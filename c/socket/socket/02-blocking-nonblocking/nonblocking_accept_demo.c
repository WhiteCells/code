#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    int listen_fd = create_tcp_server_socket(atoi(argv[1]), 1);
    if (listen_fd == -1) {
        return 1;
    }

    printf("nonblocking accept demo listening on port %s\n", argv[1]);

    for (;;) {
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(peer);
        int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);

        if (conn_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("no pending connection, accept returned EAGAIN/EWOULDBLOCK\n");
                sleep(1);
                continue;
            }
            if (errno == EINTR) {
                continue;
            }
            perror("accept");
            break;
        }

        const char msg[] = "accepted by nonblocking server\n";
        send_all(conn_fd, msg, strlen(msg));
        close(conn_fd);
    }

    close(listen_fd);
    return 0;
}
