#include "../common/net_utils.h"

#include <errno.h>
#include <stdint.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

static void *client_thread_main(void *arg) {
    int fd = (int)(intptr_t)arg;
    char buf[4096];

    for (;;) {
        ssize_t n = recv(fd, buf, sizeof(buf), 0);
        if (n > 0) {
            if (send_all(fd, buf, (size_t)n) == -1) {
                perror("send");
                break;
            }
        } else if (n == 0) {
            break;
        } else {
            if (errno == EINTR) {
                continue;
            }
            perror("recv");
            break;
        }
    }

    close(fd);
    return NULL;
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

    printf("thread-per-connection echo server listening on port %s\n", argv[1]);

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

        pthread_t tid;
        int rc = pthread_create(&tid, NULL, client_thread_main,
                                (void *)(intptr_t)conn_fd);
        if (rc != 0) {
            fprintf(stderr, "pthread_create failed: %d\n", rc);
            close(conn_fd);
            continue;
        }

        pthread_detach(tid);
    }

    close(listen_fd);
    return 0;
}
