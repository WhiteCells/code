#include <sys/socket.h>  /* for listen() */
#include <netinet/in.h>  /* for struct sockaddr_in */
#include <arpa/inet.h>   /* for inet_addr() */
#include <unistd.h>      /* for close() */
#include <string.h>      /* for bzero() */
#include <stdio.h>       /* for perror() */

int main(int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("fsd socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(10101);
    bzero(addr.sin_zero, sizeof(addr.sin_zero));

    if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        perror("bind fsd");
        return 1;
    }

    if (listen(sfd, 1) == -1) {
        perror("listen fsd");
        return 1;
    }

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int client_sfd = accept(sfd, (struct sockaddr *)&client_addr, &len);
    if (client_sfd == -1) {
        perror("fsd accept");
        return 1;
    }

    close(client_sfd);

    return 0;
}