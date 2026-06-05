#include "../common/net_utils.h"

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    int fd = create_udp_server_socket(atoi(argv[1]));
    if (fd == -1) {
        return 1;
    }

    printf("udp echo server listening on port %s\n", argv[1]);

    for (;;) {
        char buf[4096];
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(peer);

        ssize_t n = recvfrom(fd, buf, sizeof(buf), 0,
                             (struct sockaddr *)&peer, &peer_len);
        if (n == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("recvfrom");
            break;
        }

        if (sendto(fd, buf, (size_t)n, 0,
                   (struct sockaddr *)&peer, peer_len) == -1) {
            perror("sendto");
        }
    }

    close(fd);
    return 0;
}
