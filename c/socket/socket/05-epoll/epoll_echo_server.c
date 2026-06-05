#define _GNU_SOURCE
#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_EVENTS 1024

static int add_epoll_fd(int epfd, int fd, uint32_t events) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    ev.data.fd = fd;
    return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}

static void close_epoll_fd(int epfd, int fd) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    close(fd);
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

    if (add_epoll_fd(epfd, listen_fd, EPOLLIN) == -1) {
        perror("epoll_ctl listen_fd");
        close(epfd);
        close(listen_fd);
        return 1;
    }

    struct epoll_event events[MAX_EVENTS];
    printf("epoll echo server listening on port %s\n", argv[1]);

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
            int fd = events[i].data.fd;
            uint32_t ev = events[i].events;

            if (fd == listen_fd) {
                for (;;) {
                    struct sockaddr_in peer;
                    socklen_t peer_len = sizeof(peer);
                    int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);

                    if (conn_fd == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
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

                    if (add_epoll_fd(epfd, conn_fd, EPOLLIN | EPOLLRDHUP) == -1) {
                        perror("epoll_ctl conn_fd");
                        close(conn_fd);
                        continue;
                    }
                }
                continue;
            }

            if (ev & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
                close_epoll_fd(epfd, fd);
                continue;
            }

            if (ev & EPOLLIN) {
                for (;;) {
                    char buf[4096];
                    ssize_t n = recv(fd, buf, sizeof(buf), 0);

                    if (n > 0) {
                        if (send_all(fd, buf, (size_t)n) == -1) {
                            close_epoll_fd(epfd, fd);
                            break;
                        }
                    } else if (n == 0) {
                        close_epoll_fd(epfd, fd);
                        break;
                    } else {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        }
                        if (errno == EINTR) {
                            continue;
                        }
                        perror("recv");
                        close_epoll_fd(epfd, fd);
                        break;
                    }
                }
            }
        }
    }

    close(listen_fd);
    close(epfd);
    return 0;
}
