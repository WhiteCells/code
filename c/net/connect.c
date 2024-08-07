#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("socket sfd");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(10101);
    bzero(&addr.sin_zero, sizeof(addr.sin_zero));

    if (connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        perror("fsd connect");
        return 1;
    }

    
    return 0;
}