#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // struct sockaddr addr;
    // bind()
    // struct sockaddr_in addr;
    // struct in_addr addr;
    
    int fd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    struct in_addr ip;
    ip.s_addr = "127.0.0.1";
    addr.sin_addr = ip;
    bind(fd, &addr, sizeof(addr));

    printf("%d\n",
           sizeof(struct sockaddr) == sizeof(struct sockaddr_in));
    return 0;
}