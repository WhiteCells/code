#include "../common/net_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <ip> <port> <message>\n", argv[0]);
        return 1;
    }

    ignore_sigpipe();

    int fd = create_tcp_client_socket(argv[1], atoi(argv[2]));
    if (fd == -1) {
        return 1;
    }

    size_t len = strlen(argv[3]);
    if (send_all(fd, argv[3], len) == -1) {
        perror("send");
        close(fd);
        return 1;
    }

    char buf[4096];
    ssize_t n = recv(fd, buf, sizeof(buf) - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        printf("reply: %s\n", buf);
    } else if (n == 0) {
        printf("server closed connection\n");
    } else {
        perror("recv");
    }

    close(fd);
    return 0;
}
