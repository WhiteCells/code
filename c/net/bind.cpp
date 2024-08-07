#include <sys/socket.h>  /* for socket() */
#include <netinet/in.h>  /* for struct sockaddr_in */
#include <arpa/inet.h>   /* for inet_addr() */
#include <unistd.h>      /* for close() */
#include <stdio.h>       /* for perror() */
#include <string.h>      /* for memset() */

int main(int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("sfd socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

    if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        perror("sfd bind");
        return 1;
    }

    close(sfd);

    return 0;
}