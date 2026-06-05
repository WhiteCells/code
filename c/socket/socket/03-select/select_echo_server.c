#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

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

    fd_set master_set;
    FD_ZERO(&master_set);
    FD_SET(listen_fd, &master_set);
    int max_fd = listen_fd;

    printf("select echo server listening on port %s\n", argv[1]);

    for (;;) {
        fd_set read_set = master_set;
        int ready = select(max_fd + 1, &read_set, NULL, NULL, NULL);
        if (ready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("select");
            break;
        }

        for (int fd = 0; fd <= max_fd && ready > 0; fd++) {
            if (!FD_ISSET(fd, &read_set)) {
                continue;
            }
            ready--;

            if (fd == listen_fd) {
                struct sockaddr_in peer;
                socklen_t peer_len = sizeof(peer);
                int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
                if (conn_fd == -1) {
                    perror("accept");
                    continue;
                }

                if (conn_fd >= FD_SETSIZE) {
                    fprintf(stderr, "fd %d >= FD_SETSIZE, closing\n", conn_fd);
                    close(conn_fd);
                    continue;
                }

                FD_SET(conn_fd, &master_set);
                if (conn_fd > max_fd) {
                    max_fd = conn_fd;
                }
            } else {
                char buf[4096];
                ssize_t n = recv(fd, buf, sizeof(buf), 0);

                if (n > 0) {
                    if (send_all(fd, buf, (size_t)n) == -1) {
                        close(fd);
                        FD_CLR(fd, &master_set);
                    }
                } else {
                    if (n == -1 && errno != EINTR) {
                        perror("recv");
                    }
                    if (n == 0 || errno != EINTR) {
                        close(fd);
                        FD_CLR(fd, &master_set);
                        while (max_fd > listen_fd && !FD_ISSET(max_fd, &master_set)) {
                            max_fd--;
                        }
                    }
                }
            }
        }
    }

    close(listen_fd);
    return 0;
}
