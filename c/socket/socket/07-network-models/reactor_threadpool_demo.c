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

#define MAX_EVENTS 1024
#define WORKER_COUNT 4
#define BUF_SIZE 4096

enum event_kind {
    EVENT_LISTENER,
    EVENT_CLIENT,
    EVENT_WAKEUP
};

struct event_source {
    enum event_kind kind;
    void *ptr;
};

struct connection {
    struct event_source source;
    int fd;
};

struct task {
    int fd;
    size_t len;
    char data[BUF_SIZE];
    struct task *next;
};

struct queue {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    struct task *head;
    struct task *tail;
};

static struct queue work_queue = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .cond = PTHREAD_COND_INITIALIZER
};

static struct queue done_queue = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .cond = PTHREAD_COND_INITIALIZER
};

static int notify_fd = -1;

static void queue_push(struct queue *q, struct task *t, int signal_worker) {
    t->next = NULL;

    pthread_mutex_lock(&q->mutex);
    if (q->tail == NULL) {
        q->head = t;
        q->tail = t;
    } else {
        q->tail->next = t;
        q->tail = t;
    }

    if (signal_worker) {
        pthread_cond_signal(&q->cond);
    }
    pthread_mutex_unlock(&q->mutex);
}

static struct task *queue_pop_wait(struct queue *q) {
    pthread_mutex_lock(&q->mutex);
    while (q->head == NULL) {
        pthread_cond_wait(&q->cond, &q->mutex);
    }

    struct task *t = q->head;
    q->head = t->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    pthread_mutex_unlock(&q->mutex);
    return t;
}

static struct task *queue_pop_nowait(struct queue *q) {
    pthread_mutex_lock(&q->mutex);
    struct task *t = q->head;
    if (t != NULL) {
        q->head = t->next;
        if (q->head == NULL) {
            q->tail = NULL;
        }
    }
    pthread_mutex_unlock(&q->mutex);
    return t;
}

static void notify_reactor(void) {
    uint64_t one = 1;
    ssize_t n = write(notify_fd, &one, sizeof(one));
    if (n == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
        perror("write eventfd");
    }
}

static void *worker_main(void *arg) {
    (void)arg;

    for (;;) {
        struct task *t = queue_pop_wait(&work_queue);

        const char prefix[] = "worker echo: ";
        size_t prefix_len = sizeof(prefix) - 1;

        if (t->len + prefix_len <= sizeof(t->data)) {
            memmove(t->data + prefix_len, t->data, t->len);
            memcpy(t->data, prefix, prefix_len);
            t->len += prefix_len;
        }

        queue_push(&done_queue, t, 0);
        notify_reactor();
    }

    return NULL;
}

static int epoll_add(int epfd, int fd, uint32_t events, struct event_source *source) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    ev.data.ptr = source;
    return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}

static void close_connection(int epfd, struct connection *c) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, c->fd, NULL);
    close(c->fd);
    free(c);
}

static void accept_clients(int epfd, int listen_fd) {
    for (;;) {
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(peer);
        int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);

        if (conn_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return;
            }
            if (errno == EINTR) {
                continue;
            }
            perror("accept");
            return;
        }

        if (set_nonblocking(conn_fd) == -1) {
            perror("fcntl conn_fd");
            close(conn_fd);
            continue;
        }

        struct connection *c = calloc(1, sizeof(*c));
        if (c == NULL) {
            perror("calloc");
            close(conn_fd);
            continue;
        }

        c->source.kind = EVENT_CLIENT;
        c->source.ptr = c;
        c->fd = conn_fd;

        if (epoll_add(epfd, conn_fd, EPOLLIN | EPOLLRDHUP, &c->source) == -1) {
            perror("epoll_ctl add client");
            close(conn_fd);
            free(c);
        }
    }
}

static int read_client_to_work_queue(struct connection *c) {
    for (;;) {
        struct task *t = calloc(1, sizeof(*t));
        if (t == NULL) {
            perror("calloc task");
            return -1;
        }

        ssize_t n = recv(c->fd, t->data, sizeof(t->data), 0);
        if (n > 0) {
            t->fd = c->fd;
            t->len = (size_t)n;
            queue_push(&work_queue, t, 1);
            continue;
        }

        free(t);

        if (n == 0) {
            return -1;
        }

        if (errno == EINTR) {
            continue;
        }

        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        }

        perror("recv");
        return -1;
    }
}

static void drain_notify_fd(void) {
    for (;;) {
        uint64_t value;
        ssize_t n = read(notify_fd, &value, sizeof(value));
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

static void send_completed_tasks(void) {
    for (;;) {
        struct task *t = queue_pop_nowait(&done_queue);
        if (t == NULL) {
            return;
        }

        if (send_all(t->fd, t->data, t->len) == -1) {
            perror("send_all");
        }

        free(t);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    ignore_sigpipe();

    for (int i = 0; i < WORKER_COUNT; i++) {
        pthread_t tid;
        int rc = pthread_create(&tid, NULL, worker_main, NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_create failed: %s\n", strerror(rc));
            return 1;
        }
        pthread_detach(tid);
    }

    int listen_fd = create_tcp_server_socket(atoi(argv[1]), 1);
    if (listen_fd == -1) {
        return 1;
    }

    notify_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (notify_fd == -1) {
        perror("eventfd");
        close(listen_fd);
        return 1;
    }

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd == -1) {
        perror("epoll_create1");
        close(notify_fd);
        close(listen_fd);
        return 1;
    }

    struct event_source listener_source = {
        .kind = EVENT_LISTENER,
        .ptr = NULL
    };

    struct event_source wakeup_source = {
        .kind = EVENT_WAKEUP,
        .ptr = NULL
    };

    if (epoll_add(epfd, listen_fd, EPOLLIN, &listener_source) == -1) {
        perror("epoll_ctl listener");
        return 1;
    }

    if (epoll_add(epfd, notify_fd, EPOLLIN, &wakeup_source) == -1) {
        perror("epoll_ctl eventfd");
        return 1;
    }

    printf("reactor + threadpool demo listening on port %s\n", argv[1]);

    struct epoll_event events[MAX_EVENTS];
    for (;;) {
        int nready = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (nready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nready; i++) {
            struct event_source *source = events[i].data.ptr;

            if (source->kind == EVENT_LISTENER) {
                accept_clients(epfd, listen_fd);
            } else if (source->kind == EVENT_WAKEUP) {
                drain_notify_fd();
                send_completed_tasks();
            } else if (source->kind == EVENT_CLIENT) {
                struct connection *c = source->ptr;
                uint32_t ev = events[i].events;

                if (ev & EPOLLIN) {
                    if (read_client_to_work_queue(c) == -1) {
                        close_connection(epfd, c);
                        continue;
                    }
                }

                if (ev & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
                    close_connection(epfd, c);
                }
            }
        }
    }

    close(epfd);
    close(notify_fd);
    close(listen_fd);
    return 0;
}
