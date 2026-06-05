#include <arpa/inet.h>
#include <netinet/in.h>
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

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons((uint16_t)atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &server.sin_addr) != 1) {
        fprintf(stderr, "invalid IPv4 address: %s\n", argv[1]);
        close(fd);
        return 1;
    }

    size_t len = strlen(argv[3]);
    if (sendto(fd, argv[3], len, 0,
               (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("sendto");
        close(fd);
        return 1;
    }

    char buf[4096];
    ssize_t n = recvfrom(fd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    if (n > 0) {
        buf[n] = '\0';
        printf("reply: %s\n", buf);
    } else if (n == -1) {
        perror("recvfrom");
    }

    close(fd);
    return 0;
}
