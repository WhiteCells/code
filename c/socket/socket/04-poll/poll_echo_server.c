#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENTS 1024

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    ignore_sigpipe();

    int listen_fd = create_tcp_server_socket(atoi(argv[1]), 0);
    if (listen_fd == -1) {
        return 1;
    }

    struct pollfd fds[MAX_CLIENTS + 1];
    nfds_t nfds = 1;
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    printf("poll echo server listening on port %s\n", argv[1]);

    for (;;) {
        int ready = poll(fds, nfds, -1);
        if (ready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("poll");
            break;
        }

        for (nfds_t i = 0; i < nfds && ready > 0; i++) {
            if (fds[i].revents == 0) {
                continue;
            }
            ready--;

            if (fds[i].fd == listen_fd) {
                if (fds[i].revents & POLLIN) {
                    struct sockaddr_in peer;
                    socklen_t peer_len = sizeof(peer);
                    int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
                    if (conn_fd == -1) {
                        perror("accept");
                        continue;
                    }

                    if (nfds == MAX_CLIENTS + 1) {
                        fprintf(stderr, "too many clients, closing fd %d\n", conn_fd);
                        close(conn_fd);
                        continue;
                    }

                    fds[nfds].fd = conn_fd;
                    fds[nfds].events = POLLIN;
                    fds[nfds].revents = 0;
                    nfds++;
                }
            } else {
                if (fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                    close(fds[i].fd);
                    fds[i] = fds[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }

                if (fds[i].revents & POLLIN) {
                    char buf[4096];
                    ssize_t n = recv(fds[i].fd, buf, sizeof(buf), 0);

                    if (n > 0) {
                        if (send_all(fds[i].fd, buf, (size_t)n) == -1) {
                            close(fds[i].fd);
                            fds[i] = fds[nfds - 1];
                            nfds--;
                            i--;
                        }
                    } else {
                        if (n == -1 && errno != EINTR) {
                            perror("recv");
                        }
                        if (n == 0 || errno != EINTR) {
                            close(fds[i].fd);
                            fds[i] = fds[nfds - 1];
                            nfds--;
                            i--;
                        }
                    }
                }
            }
        }
    }

    for (nfds_t i = 0; i < nfds; i++) {
        close(fds[i].fd);
    }
    return 0;
}
