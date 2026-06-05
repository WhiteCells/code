#define _GNU_SOURCE
#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_EVENTS 1024
#define OUT_CAP (64 * 1024)
#define HIGH_WATER (48 * 1024)

struct connection {
    int fd;
    int is_listener;
    int want_close;
    size_t out_sent;
    size_t out_len;
    char out[OUT_CAP];
};

static size_t pending_bytes(const struct connection *c) {
    return c->out_len - c->out_sent;
}

static void compact_output(struct connection *c) {
    if (c->out_sent == 0) {
        return;
    }

    if (c->out_sent == c->out_len) {
        c->out_sent = 0;
        c->out_len = 0;
        return;
    }

    memmove(c->out, c->out + c->out_sent, c->out_len - c->out_sent);
    c->out_len -= c->out_sent;
    c->out_sent = 0;
}

static uint32_t connection_events(const struct connection *c) {
    uint32_t events = EPOLLRDHUP;

    if (!c->want_close && pending_bytes(c) < HIGH_WATER) {
        events |= EPOLLIN;
    }

    if (pending_bytes(c) > 0) {
        events |= EPOLLOUT;
    }

    return events;
}

static int epoll_add_connection(int epfd, struct connection *c) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = c->is_listener ? EPOLLIN : connection_events(c);
    ev.data.ptr = c;
    return epoll_ctl(epfd, EPOLL_CTL_ADD, c->fd, &ev);
}

static int epoll_mod_connection(int epfd, struct connection *c) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = connection_events(c);
    ev.data.ptr = c;
    return epoll_ctl(epfd, EPOLL_CTL_MOD, c->fd, &ev);
}

static void close_connection(int epfd, struct connection *c) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, c->fd, NULL);
    close(c->fd);
    free(c);
}

static int flush_output(struct connection *c) {
    while (c->out_sent < c->out_len) {
        ssize_t n = send(c->fd,
                         c->out + c->out_sent,
                         c->out_len - c->out_sent,
                         MSG_NOSIGNAL);
        if (n > 0) {
            c->out_sent += (size_t)n;
            continue;
        }

        if (n == -1 && errno == EINTR) {
            continue;
        }

        if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            compact_output(c);
            return 0;
        }

        return -1;
    }

    compact_output(c);
    return 0;
}

static int append_echo_data(struct connection *c, const char *buf, size_t len) {
    compact_output(c);

    if (len > OUT_CAP - c->out_len) {
        if (flush_output(c) == -1) {
            return -1;
        }
        compact_output(c);
    }

    if (len > OUT_CAP - c->out_len) {
        fprintf(stderr, "fd %d output buffer full, closing\n", c->fd);
        c->want_close = 1;
        return 0;
    }

    memcpy(c->out + c->out_len, buf, len);
    c->out_len += len;
    return 0;
}

static int read_available(struct connection *c) {
    for (;;) {
        char buf[4096];
        ssize_t n = recv(c->fd, buf, sizeof(buf), 0);

        if (n > 0) {
            if (append_echo_data(c, buf, (size_t)n) == -1) {
                return -1;
            }

            if (flush_output(c) == -1) {
                return -1;
            }

            if (pending_bytes(c) >= HIGH_WATER) {
                break;
            }

            continue;
        }

        if (n == 0) {
            c->want_close = 1;
            break;
        }

        if (errno == EINTR) {
            continue;
        }

        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            break;
        }

        return -1;
    }

    return 0;
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

        c->fd = conn_fd;
        if (epoll_add_connection(epfd, c) == -1) {
            perror("epoll_ctl add client");
            close(conn_fd);
            free(c);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    ignore_sigpipe();

    int listen_fd = create_tcp_server_socket(atoi(argv[1]), 1);
    if (listen_fd == -1) {
        return 1;
    }

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd == -1) {
        perror("epoll_create1");
        close(listen_fd);
        return 1;
    }

    struct connection listener;
    memset(&listener, 0, sizeof(listener));
    listener.fd = listen_fd;
    listener.is_listener = 1;

    if (epoll_add_connection(epfd, &listener) == -1) {
        perror("epoll_ctl add listener");
        close(epfd);
        close(listen_fd);
        return 1;
    }

    struct epoll_event events[MAX_EVENTS];
    printf("buffered epoll echo server listening on port %s\n", argv[1]);

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
            struct connection *c = events[i].data.ptr;
            uint32_t ev = events[i].events;

            if (c->is_listener) {
                accept_clients(epfd, c->fd);
                continue;
            }

            int fatal = 0;

            if (ev & EPOLLIN) {
                if (read_available(c) == -1) {
                    fatal = 1;
                }
            }

            if (!fatal && (ev & EPOLLOUT)) {
                if (flush_output(c) == -1) {
                    fatal = 1;
                }
            }

            if (ev & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
                c->want_close = 1;
            }

            if (fatal) {
                close_connection(epfd, c);
                continue;
            }

            if (c->want_close && pending_bytes(c) == 0) {
                close_connection(epfd, c);
                continue;
            }

            if (epoll_mod_connection(epfd, c) == -1) {
                perror("epoll_ctl mod client");
                close_connection(epfd, c);
            }
        }
    }

    close(listen_fd);
    close(epfd);
    return 0;
}
