#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

int create_tcp_server_socket(int port, int nonblocking);
int create_tcp_client_socket(const char *ip, int port);
int create_udp_server_socket(int port);
int set_nonblocking(int fd);
int send_all(int fd, const void *buf, size_t len);
void ignore_sigpipe(void);

#endif
