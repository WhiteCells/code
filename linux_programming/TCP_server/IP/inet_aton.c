/*
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    int inet_aton(const char *cp, struct in_addr *inp);
        parameter:
            - cp: 
            - inp:

        return:
            - 
 */

#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct in_addr ia;
    in_addr_t ip = inet_addr("127.0.0.1");
    ia.s_addr = ip;
    printf("0x%x\n", ia.s_addr);
    printf("%u\n", ip);
    printf("%s\n", inet_ntoa(ia));

    int num = 0x123456789;
    char *p = (char *)&num;
    if (*p == 0x12) {
        printf("big endian");
    } else {
        printf("litter endian");
    }

    return 0;
}