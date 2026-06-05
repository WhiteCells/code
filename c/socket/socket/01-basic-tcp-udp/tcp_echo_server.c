#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

static void serve_client(int conn_fd) {
    char buf[4096];

    for (;;) {
        ssize_t n = recv(conn_fd, buf, sizeof(buf), 0);
        if (n > 0) {
            if (send_all(conn_fd, buf, (size_t)n) == -1) {
                perror("send");
                return;
            }
        } else if (n == 0) {
            return;
        } else {
            if (errno == EINTR) {
                continue;
            }
            perror("recv");
            return;
        }
    }
}

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

    printf("tcp echo server listening on port %s\n", argv[1]);

    for (;;) {
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(peer);
        int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
        if (conn_fd == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("accept");
            break;
        }

        serve_client(conn_fd);
        close(conn_fd);
    }

    close(listen_fd);
    return 0;
}
