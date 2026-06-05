#define _GNU_SOURCE
#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/socket.h>
#include <unistd.h>

#define SUB_REACTOR_COUNT 2
#define MAX_EVENTS 1024

struct fd_node {
    int fd;
    struct fd_node *next;
};

struct sub_reactor {
    int id;
    int epfd;
    int notify_fd;
    pthread_t thread;
    pthread_mutex_t mutex;
    struct fd_node *head;
    struct fd_node *tail;
};

struct connection {
    struct event_source *source;
    int fd;
};

struct event_source {
    int is_notify;
    void *ptr;
};

static struct sub_reactor reactors[SUB_REACTOR_COUNT];

static void enqueue_fd(struct sub_reactor *r, int fd) {
    struct fd_node *node = malloc(sizeof(*node));
    if (node == NULL) {
        perror("malloc fd_node");
        close(fd);
        return;
    }

    node->fd = fd;
    node->next = NULL;

    pthread_mutex_lock(&r->mutex);
    if (r->tail == NULL) {
        r->head = node;
        r->tail = node;
    } else {
        r->tail->next = node;
        r->tail = node;
    }
    pthread_mutex_unlock(&r->mutex);

    uint64_t one = 1;
    ssize_t n = write(r->notify_fd, &one, sizeof(one));
    if (n == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
        perror("write eventfd");
    }
}

static int dequeue_fd(struct sub_reactor *r) {
    pthread_mutex_lock(&r->mutex);
    struct fd_node *node = r->head;
    if (node == NULL) {
        pthread_mutex_unlock(&r->mutex);
        return -1;
    }

    r->head = node->next;
    if (r->head == NULL) {
        r->tail = NULL;
    }
    pthread_mutex_unlock(&r->mutex);

    int fd = node->fd;
    free(node);
    return fd;
}

static void drain_eventfd(int fd) {
    for (;;) {
        uint64_t value;
        ssize_t n = read(fd, &value, sizeof(value));
        if (n == sizeof(value)) {
            continue;
        }
        if (n == -1 && errno == EINTR) {
            continue;
        }
        if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            return;
        }
        return;
    }
}

static int add_client_fd(struct sub_reactor *r, int fd) {
    struct connection *c = calloc(1, sizeof(*c));
    if (c == NULL) {
        perror("calloc connection");
        close(fd);
        return -1;
    }

    struct event_source *source = calloc(1, sizeof(*source));
    if (source == NULL) {
        perror("calloc event_source");
        close(fd);
        free(c);
        return -1;
    }

    source->is_notify = 0;
    source->ptr = c;

    c->source = source;
    c->fd = fd;

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN | EPOLLRDHUP;
    ev.data.ptr = source;

    if (epoll_ctl(r->epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        perror("epoll_ctl add client");
        close(fd);
        free(source);
        free(c);
        return -1;
    }

    return 0;
}

static void close_client(struct sub_reactor *r, struct connection *c) {
    epoll_ctl(r->epfd, EPOLL_CTL_DEL, c->fd, NULL);
    close(c->fd);
    free(c->source);
    free(c);
}

static void handle_client_event(struct sub_reactor *r, struct connection *c,
                                uint32_t events) {
    if (events & EPOLLIN) {
        for (;;) {
            char buf[4096];
            ssize_t n = recv(c->fd, buf, sizeof(buf), 0);

            if (n > 0) {
                if (send_all(c->fd, buf, (size_t)n) == -1) {
                    close_client(r, c);
                    return;
                }
                continue;
            }

            if (n == 0) {
                close_client(r, c);
                return;
            }

            if (errno == EINTR) {
                continue;
            }

            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            }

            perror("recv");
            close_client(r, c);
            return;
        }
    }

    if (events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
        close_client(r, c);
    }
}

static void register_pending_fds(struct sub_reactor *r) {
    for (;;) {
        int fd = dequeue_fd(r);
        if (fd == -1) {
            return;
        }
        add_client_fd(r, fd);
    }
}

static void *sub_reactor_main(void *arg) {
    struct sub_reactor *r = arg;
    struct epoll_event events[MAX_EVENTS];

    for (;;) {
        int nready = epoll_wait(r->epfd, events, MAX_EVENTS, -1);
        if (nready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("epoll_wait sub reactor");
            return NULL;
        }

        for (int i = 0; i < nready; i++) {
            struct event_source *source = events[i].data.ptr;
            if (source->is_notify) {
                drain_eventfd(r->notify_fd);
                register_pending_fds(r);
            } else {
                struct connection *c = source->ptr;
                handle_client_event(r, c, events[i].events);
            }
        }
    }
}

static int init_sub_reactor(struct sub_reactor *r, int id) {
    r->id = id;
    r->epfd = epoll_create1(EPOLL_CLOEXEC);
    if (r->epfd == -1) {
        perror("epoll_create1");
        return -1;
    }

    r->notify_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (r->notify_fd == -1) {
        perror("eventfd");
        close(r->epfd);
        return -1;
    }

    pthread_mutex_init(&r->mutex, NULL);
    r->head = NULL;
    r->tail = NULL;

    struct event_source *notify_source = calloc(1, sizeof(*notify_source));
    if (notify_source == NULL) {
        perror("calloc notify_source");
        close(r->notify_fd);
        close(r->epfd);
        return -1;
    }

    notify_source->is_notify = 1;
    notify_source->ptr = r;

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.ptr = notify_source;
    if (epoll_ctl(r->epfd, EPOLL_CTL_ADD, r->notify_fd, &ev) == -1) {
        perror("epoll_ctl eventfd");
        free(notify_source);
        close(r->notify_fd);
        close(r->epfd);
        return -1;
    }

    int rc = pthread_create(&r->thread, NULL, sub_reactor_main, r);
    if (rc != 0) {
        fprintf(stderr, "pthread_create sub reactor failed: %s\n", strerror(rc));
        free(notify_source);
        close(r->notify_fd);
        close(r->epfd);
        return -1;
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    ignore_sigpipe();

    for (int i = 0; i < SUB_REACTOR_COUNT; i++) {
        if (init_sub_reactor(&reactors[i], i) == -1) {
            return 1;
        }
    }

    int listen_fd = create_tcp_server_socket(atoi(argv[1]), 1);
    if (listen_fd == -1) {
        return 1;
    }

    printf("multi-reactor demo listening on port %s with %d sub reactors\n",
           argv[1], SUB_REACTOR_COUNT);

    int next = 0;
    for (;;) {
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(peer);
        int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);

        if (conn_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                usleep(1000);
                continue;
            }
            if (errno == EINTR) {
                continue;
            }
            perror("accept");
            break;
        }

        if (set_nonblocking(conn_fd) == -1) {
            perror("fcntl conn_fd");
            close(conn_fd);
            continue;
        }

        enqueue_fd(&reactors[next], conn_fd);
        next = (next + 1) % SUB_REACTOR_COUNT;
    }

    close(listen_fd);
    return 0;
}
