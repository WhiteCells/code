# Linux/Unix Socket 网络编程教程

本文面向已经有 C 语言基础、了解进程、文件描述符、系统调用等操作系统概念，但还不熟悉网络编程的读者。

我们会从 socket 的基本模型讲起，再进入阻塞/非阻塞 I/O，最后重点比较 `select`、`poll`、`epoll` 三种 I/O 多路复用机制。文中的示例都围绕一个经典场景：TCP echo server，即客户端发来什么，服务器原样发回什么。

---

## 1. Socket 基础

### 1.1 socket 是什么

在 Unix/Linux 中，很多 I/O 对象都用“文件描述符”表示：普通文件、管道、终端、设备，以及网络连接。

`socket` 可以理解为一种用于网络通信的文件描述符。创建 socket 后，程序可以像读写文件一样，通过 `send`、`recv`、`read`、`write` 等系统调用收发网络数据。

一个 TCP 连接通常由四元组唯一标识：

| 字段 | 说明 |
| --- | --- |
| 本地 IP | 本机使用的 IP 地址 |
| 本地端口 | 本机端口 |
| 对端 IP | 远端主机 IP 地址 |
| 对端端口 | 远端端口 |

例如：

```text
192.168.1.10:50000 <-> 203.0.113.8:80
```

在程序里，socket 本质上是一个 `int fd`：

```c
int fd = socket(AF_INET, SOCK_STREAM, 0);
```

其中：

- `AF_INET` 表示 IPv4。
- `SOCK_STREAM` 表示 TCP。
- `0` 表示使用该协议族和 socket 类型的默认协议。

---

### 1.2 TCP socket 与 UDP socket

常见 socket 类型主要有两类：

| 类型 | C 参数 | 协议 | 特点 |
| --- | --- | --- | --- |
| 流式 socket | `SOCK_STREAM` | TCP | 面向连接、可靠、有序、字节流 |
| 数据报 socket | `SOCK_DGRAM` | UDP | 无连接、不保证可靠、不保证顺序、保留消息边界 |

#### TCP socket

TCP 是面向连接的协议。通信前，客户端需要先连接服务器；连接建立后，双方得到的是一条可靠的字节流。

TCP 的特点：

- 需要建立连接。
- 保证数据可靠到达。
- 保证数据顺序。
- 不保留应用层消息边界。
- 适合文件传输、HTTP、数据库连接、SSH 等可靠传输场景。

TCP server 通常会：

1. 创建监听 socket。
2. 绑定 IP 和端口。
3. 进入监听状态。
4. 接受客户端连接。
5. 在连接 socket 上收发数据。

TCP client 通常会：

1. 创建 socket。
2. 连接服务器。
3. 在连接 socket 上收发数据。
4. 关闭连接。

#### UDP socket

UDP 是无连接的数据报协议。发送方可以直接向某个地址发送一份数据报，接收方一次收到一个数据报。

UDP 的特点：

- 不需要建立连接。
- 不保证可靠到达。
- 不保证顺序。
- 保留消息边界。
- 适合 DNS、日志上报、实时音视频、游戏状态同步等场景。

UDP server 通常会：

1. 创建 UDP socket。
2. 绑定 IP 和端口。
3. 使用 `recvfrom` 接收数据和对端地址。
4. 使用 `sendto` 回复数据。

UDP client 通常会：

1. 创建 UDP socket。
2. 使用 `sendto` 发数据。
3. 使用 `recvfrom` 收回复。

注意：UDP 也可以调用 `connect`。这并不是建立 TCP 那样的连接，而是为 UDP socket 绑定默认对端地址，之后可以使用 `send` / `recv`，并且内核会过滤非该对端发来的数据。

---

### 1.3 TCP 服务端和客户端基本通信流程

#### TCP server 流程

```text
socket()
  |
bind()
  |
listen()
  |
accept()
  |
recv() / send()
  |
close()
```

核心含义：

- `socket()`：创建一个 socket fd。
- `bind()`：把 socket 绑定到本地 IP 和端口。
- `listen()`：把 socket 变成监听 socket，用于等待连接。
- `accept()`：从已完成连接队列中取出一个客户端连接，返回新的连接 fd。
- `recv()` / `send()`：在连接 fd 上收发数据。
- `close()`：关闭 fd。

监听 socket 和连接 socket 是两个不同的 fd：

```text
listen_fd: 只负责 accept 新连接
conn_fd:   只负责和某个客户端收发数据
```

#### TCP client 流程

```text
socket()
  |
connect()
  |
send() / recv()
  |
close()
```

客户端一般不需要显式调用 `bind()`，因为内核会自动选择本地 IP 和临时端口。

---

### 1.4 常见系统调用

#### socket

```c
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

示例：

```c
int fd = socket(AF_INET, SOCK_STREAM, 0);
if (fd == -1) {
    perror("socket");
}
```

常见参数：

- `domain`
  - `AF_INET`：IPv4。
  - `AF_INET6`：IPv6。
  - `AF_UNIX`：Unix domain socket，本机进程间通信。
- `type`
  - `SOCK_STREAM`：TCP。
  - `SOCK_DGRAM`：UDP。
- `protocol`
  - 通常填 `0`。

#### bind

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

`bind` 把 socket 绑定到本地地址：

```c
struct sockaddr_in addr;
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = htonl(INADDR_ANY);
addr.sin_port = htons(8080);

if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("bind");
}
```

几个容易混淆的点：

- `INADDR_ANY` 表示监听本机所有网卡地址。
- `htons` 把 16 位端口从主机字节序转换为网络字节序。
- `htonl` 把 32 位整数从主机字节序转换为网络字节序。

#### listen

```c
int listen(int sockfd, int backlog);
```

`listen` 把 TCP socket 变成监听 socket。

```c
if (listen(fd, SOMAXCONN) == -1) {
    perror("listen");
}
```

`backlog` 和连接队列相关。它不是“最大并发连接数”的简单等价物，而是影响内核为监听 socket 维护的已完成连接队列长度。实际行为还会受到系统参数限制，例如 Linux 上的 `net.core.somaxconn`。

#### accept

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

`accept` 从监听 socket 的已完成连接队列中取出一个连接，返回新的连接 fd：

```c
struct sockaddr_in peer;
socklen_t len = sizeof(peer);
int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &len);
if (conn_fd == -1) {
    perror("accept");
}
```

后续收发数据要使用 `conn_fd`，不是 `listen_fd`。

#### connect

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

客户端用 `connect` 连接服务器：

```c
struct sockaddr_in server;
memset(&server, 0, sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(8080);
inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

if (connect(fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
}
```

阻塞 socket 上，`connect` 会等待连接成功或失败。非阻塞 socket 上，`connect` 常见返回 `-1` 且 `errno == EINPROGRESS`，表示连接正在进行中，之后通常通过 `select` / `poll` / `epoll` 等待 socket 可写，再用 `getsockopt(fd, SOL_SOCKET, SO_ERROR, ...)` 判断连接结果。

#### send

```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

`send` 发送数据：

```c
ssize_t n = send(conn_fd, buf, len, 0);
if (n == -1) {
    perror("send");
}
```

注意：一次 `send` 不一定发送完整个缓冲区。返回值 `n` 表示实际写入内核发送缓冲区的字节数。应用层需要处理“短写”。

#### recv

```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

`recv` 接收数据：

```c
char buf[4096];
ssize_t n = recv(conn_fd, buf, sizeof(buf), 0);
if (n > 0) {
    // 收到 n 字节
} else if (n == 0) {
    // 对端正常关闭连接
} else {
    perror("recv");
}
```

返回值含义：

| 返回值 | 含义 |
| --- | --- |
| `> 0` | 收到的字节数 |
| `0` | 对端有序关闭连接 |
| `-1` | 出错，查看 `errno` |

TCP 是字节流，所以 `recv` 读到的数据长度不一定等于对端某次 `send` 的长度。

#### close

```c
int close(int fd);
```

关闭 socket fd：

```c
close(conn_fd);
```

关闭连接 fd 会释放本进程对该连接的引用。如果 fd 泄漏，内核资源会被占住，长时间运行的服务会越来越不稳定。

---

### 1.5 同步、异步与事件驱动

网络编程里常见几种 I/O 模型：

| 模型 | 说明 |
| --- | --- |
| 阻塞 I/O | 调用 `recv` 时没有数据，线程睡眠等待 |
| 非阻塞 I/O | 调用立即返回，没有数据时返回 `EAGAIN` / `EWOULDBLOCK` |
| I/O 多路复用 | 用 `select` / `poll` / `epoll` 同时等待多个 fd 的事件 |
| 信号驱动 I/O | 通过 `SIGIO` 通知 I/O 事件，实际项目较少使用 |
| 异步 I/O | 发起操作后由内核或运行时完成并通知结果 |

在 Linux 网络服务中，最常见的高并发模型不是“每个连接一个线程阻塞读写”，而是：

```text
非阻塞 socket + epoll + 事件循环
```

更上层的异步网络库，例如 libevent、libev、libuv、Boost.Asio、nginx 的事件模块，本质上都在封装类似思想：程序注册自己关心的事件，当 fd 可读、可写或出错时，再执行对应回调或任务。

近年来 Linux 还提供了 `io_uring`，它能以提交队列和完成队列的方式处理异步 I/O。对普通网络服务入门来说，先掌握非阻塞 socket 与 I/O 多路复用更重要。

---

## 2. 阻塞与非阻塞 I/O

### 2.1 阻塞 socket 的行为

默认创建出来的 socket 通常是阻塞的。

阻塞 socket 上：

- `accept`：没有新连接时会一直等待。
- `recv`：没有数据时会一直等待。
- `send`：发送缓冲区满时可能等待。
- `connect`：连接建立或失败前可能等待。

阻塞 I/O 写起来简单，例如：

```c
int conn_fd = accept(listen_fd, NULL, NULL);
recv(conn_fd, buf, sizeof(buf), 0);
send(conn_fd, buf, n, 0);
```

但它的问题也明显：如果当前线程阻塞在某个连接的 `recv` 上，就无法处理其他连接。

一种简单扩展方式是“一连接一线程”：

```text
主线程 accept
每来一个连接创建一个线程
每个线程阻塞 recv/send
```

这种模型在低并发、小工具、教学代码里很方便。但连接数上来后，会遇到：

- 线程数量过多。
- 上下文切换成本高。
- 每个线程都需要栈内存。
- 慢连接会长期占住线程。

---

### 2.2 非阻塞 socket 的行为

非阻塞 socket 不会因为“暂时没有条件完成操作”而睡眠等待，而是立即返回。

可以用 `fcntl` 设置非阻塞：

```c
#include <fcntl.h>

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
```

非阻塞 socket 上：

- `accept`：没有新连接，返回 `-1`，`errno` 为 `EAGAIN` 或 `EWOULDBLOCK`。
- `recv`：没有数据，返回 `-1`，`errno` 为 `EAGAIN` 或 `EWOULDBLOCK`。
- `send`：发送缓冲区暂时写不进去，返回 `-1`，`errno` 为 `EAGAIN` 或 `EWOULDBLOCK`。
- `connect`：连接进行中，返回 `-1`，`errno` 为 `EINPROGRESS`。

非阻塞 I/O 的典型使用方式不是死循环一直调用 `recv`，而是配合事件通知机制：

```text
epoll_wait 告诉你 fd 可读
  |
循环 recv，直到读完
  |
遇到 EAGAIN，说明暂时没有更多数据
  |
回到 epoll_wait
```

---

### 2.3 EAGAIN / EWOULDBLOCK 的含义

`EAGAIN` 和 `EWOULDBLOCK` 都表示：

> 这次操作现在无法立即完成，请稍后再试。

在 Linux 上，这两个宏通常数值相同；在可移植代码中，建议同时判断：

```c
if (errno == EAGAIN || errno == EWOULDBLOCK) {
    // 不是致命错误，稍后再试
}
```

常见场景：

- 非阻塞 `recv` 没有数据可读。
- 非阻塞 `send` 发送缓冲区满。
- 非阻塞 `accept` 没有可取的新连接。

它不是连接断开，也不是系统故障，而是事件驱动程序里很正常的状态。

---

### 2.4 为什么高并发服务通常需要非阻塞 I/O

假设服务器同时维护 10 万个连接。大部分时间里，多数连接并没有数据可读或可写。如果每个连接一个线程，资源消耗会非常高。

更常见的做法是：

1. 所有连接 fd 设置为非阻塞。
2. 用 `epoll` 等机制监听这些 fd 的可读、可写、错误事件。
3. 事件到来时才处理对应连接。
4. 处理到 `EAGAIN` 就停止，回到事件循环。

这样一个线程可以管理大量连接。实际服务通常会使用多个 worker 进程或线程，每个 worker 有自己的事件循环，从而利用多核 CPU。

---

## 3. I/O 多路复用

### 3.1 为什么需要 select / poll / epoll

阻塞 I/O 面临的问题是：一个线程阻塞在一个 fd 上，就无法同时等其他 fd。

I/O 多路复用解决的是：

> 一个线程如何同时等待多个 fd 的事件？

它的核心模型是：

```text
把一组 fd 交给内核
  |
内核等待其中任意 fd 变得可读/可写/异常
  |
系统调用返回
  |
用户态遍历就绪 fd 并处理
```

常见机制：

- `select`：历史悠久，可移植性好，但 fd 数量和性能有明显限制。
- `poll`：去掉了 `select` 的固定 fd 集合限制，但每次仍需线性扫描。
- `epoll`：Linux 特有，适合大量连接和高并发事件循环。

---

### 3.2 select

#### 原理

`select` 使用 `fd_set` 表示一组 fd。调用前，程序把关心的 fd 放入读集合、写集合、异常集合；调用返回后，集合会被内核修改，只保留已经就绪的 fd。

函数原型：

```c
#include <sys/select.h>

int select(int nfds,
           fd_set *readfds,
           fd_set *writefds,
           fd_set *exceptfds,
           struct timeval *timeout);
```

参数说明：

- `nfds`：需要检查的最大 fd 值加 1。
- `readfds`：关心可读事件的 fd 集合。
- `writefds`：关心可写事件的 fd 集合。
- `exceptfds`：关心异常事件的 fd 集合。
- `timeout`：超时时间，传 `NULL` 表示一直等待。

因为 `select` 会修改传入的 `fd_set`，所以每次调用前都要重新构造集合。

#### select 核心示例

下面是一个 TCP echo server 的完整 `select` 版本。它能同时处理多个客户端连接，但仍然是单线程。

编译：

```bash
gcc -Wall -Wextra -O2 select_echo_server.c -o select_echo_server
```

运行：

```bash
./select_echo_server 8080
```

测试：

```bash
nc 127.0.0.1 8080
```

代码关键逻辑：

- `master_set` 保存所有需要监听的 fd。
- 每次调用 `select` 前复制到 `read_set`，因为 `select` 会修改集合。
- `listen_fd` 可读表示有新连接。
- 客户端 fd 可读表示可以 `recv`。
- `recv` 返回 `0` 表示客户端关闭连接，需要 `close` 并从集合移除。

```c
// select_echo_server.c
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

static int create_listen_socket(int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        perror("setsockopt");
        close(fd);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((uint16_t)port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(fd);
        exit(1);
    }

    if (listen(fd, SOMAXCONN) == -1) {
        perror("listen");
        close(fd);
        exit(1);
    }

    return fd;
}

static void send_all(int fd, const char *buf, ssize_t len) {
    ssize_t sent = 0;
    while (sent < len) {
        ssize_t n = send(fd, buf + sent, (size_t)(len - sent), 0);
        if (n > 0) {
            sent += n;
        } else if (n == -1 && errno == EINTR) {
            continue;
        } else {
            return;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    signal(SIGPIPE, SIG_IGN);

    int listen_fd = create_listen_socket(atoi(argv[1]));
    fd_set master_set;
    FD_ZERO(&master_set);
    FD_SET(listen_fd, &master_set);
    int max_fd = listen_fd;

    printf("select echo server listening on port %s\n", argv[1]);

    for (;;) {
        fd_set read_set = master_set;
        int ready = select(max_fd + 1, &read_set, NULL, NULL, NULL);
        if (ready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("select");
            break;
        }

        for (int fd = 0; fd <= max_fd && ready > 0; fd++) {
            if (!FD_ISSET(fd, &read_set)) {
                continue;
            }
            ready--;

            if (fd == listen_fd) {
                struct sockaddr_in peer;
                socklen_t peer_len = sizeof(peer);
                int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
                if (conn_fd == -1) {
                    perror("accept");
                    continue;
                }

                if (conn_fd >= FD_SETSIZE) {
                    fprintf(stderr, "fd %d >= FD_SETSIZE, closing\n", conn_fd);
                    close(conn_fd);
                    continue;
                }

                FD_SET(conn_fd, &master_set);
                if (conn_fd > max_fd) {
                    max_fd = conn_fd;
                }
            } else {
                char buf[4096];
                ssize_t n = recv(fd, buf, sizeof(buf), 0);
                if (n > 0) {
                    send_all(fd, buf, n);
                } else if (n == 0) {
                    close(fd);
                    FD_CLR(fd, &master_set);
                    while (max_fd > listen_fd && !FD_ISSET(max_fd, &master_set)) {
                        max_fd--;
                    }
                } else {
                    if (errno != EINTR) {
                        perror("recv");
                        close(fd);
                        FD_CLR(fd, &master_set);
                    }
                }
            }
        }
    }

    close(listen_fd);
    return 0;
}
```

#### select 优点

- 可移植性好，很多 Unix-like 系统都支持。
- API 历史悠久，适合学习 I/O 多路复用基础模型。
- 对少量 fd 的简单程序足够用。

#### select 缺点

- `FD_SETSIZE` 限制明显，常见默认值是 1024。
- 每次调用都要重新设置 `fd_set`。
- 每次返回后需要从 `0` 扫描到 `max_fd`。
- 用户态和内核态之间需要反复拷贝 fd 集合。
- 不适合大量连接。

---

### 3.3 poll

#### 原理

`poll` 使用 `struct pollfd` 数组描述 fd 和关心的事件。

函数原型：

```c
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

结构体：

```c
struct pollfd {
    int fd;
    short events;
    short revents;
};
```

字段含义：

- `fd`：要监听的文件描述符。
- `events`：程序关心的事件，比如 `POLLIN`、`POLLOUT`。
- `revents`：调用返回后，内核填入实际发生的事件。

与 `select` 相比，`poll` 不受 `FD_SETSIZE` 限制，监听多少 fd 取决于数组大小和系统资源限制。但它仍然需要每次传入整个数组，并在返回后线性扫描。

#### poll 核心示例

下面是 TCP echo server 的完整 `poll` 版本。

编译：

```bash
gcc -Wall -Wextra -O2 poll_echo_server.c -o poll_echo_server
```

运行：

```bash
./poll_echo_server 8080
```

代码关键逻辑：

- `fds[0]` 固定保存 `listen_fd`。
- 新连接到来时，把 `conn_fd` 追加到 `pollfd` 数组。
- 某个客户端关闭后，用数组最后一个元素覆盖当前位置，避免中间留下空洞。
- `revents` 里出现 `POLLIN` 表示可读，出现 `POLLERR` / `POLLHUP` / `POLLNVAL` 表示需要关闭。

```c
// poll_echo_server.c
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENTS 1024

static int create_listen_socket(int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        perror("setsockopt");
        close(fd);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((uint16_t)port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(fd);
        exit(1);
    }

    if (listen(fd, SOMAXCONN) == -1) {
        perror("listen");
        close(fd);
        exit(1);
    }

    return fd;
}

static void send_all(int fd, const char *buf, ssize_t len) {
    ssize_t sent = 0;
    while (sent < len) {
        ssize_t n = send(fd, buf + sent, (size_t)(len - sent), 0);
        if (n > 0) {
            sent += n;
        } else if (n == -1 && errno == EINTR) {
            continue;
        } else {
            return;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    signal(SIGPIPE, SIG_IGN);

    int listen_fd = create_listen_socket(atoi(argv[1]));
    struct pollfd fds[MAX_CLIENTS + 1];
    nfds_t nfds = 1;

    fds[0].fd = listen_fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    printf("poll echo server listening on port %s\n", argv[1]);

    for (;;) {
        int ready = poll(fds, nfds, -1);
        if (ready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("poll");
            break;
        }

        for (nfds_t i = 0; i < nfds && ready > 0; i++) {
            if (fds[i].revents == 0) {
                continue;
            }
            ready--;

            if (fds[i].fd == listen_fd) {
                if (fds[i].revents & POLLIN) {
                    struct sockaddr_in peer;
                    socklen_t peer_len = sizeof(peer);
                    int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
                    if (conn_fd == -1) {
                        perror("accept");
                        continue;
                    }

                    if (nfds == MAX_CLIENTS + 1) {
                        fprintf(stderr, "too many clients, closing fd %d\n", conn_fd);
                        close(conn_fd);
                        continue;
                    }

                    fds[nfds].fd = conn_fd;
                    fds[nfds].events = POLLIN;
                    fds[nfds].revents = 0;
                    nfds++;
                }
            } else {
                if (fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                    close(fds[i].fd);
                    fds[i] = fds[nfds - 1];
                    nfds--;
                    i--;
                    continue;
                }

                if (fds[i].revents & POLLIN) {
                    char buf[4096];
                    ssize_t n = recv(fds[i].fd, buf, sizeof(buf), 0);
                    if (n > 0) {
                        send_all(fds[i].fd, buf, n);
                    } else {
                        if (n == -1) {
                            perror("recv");
                        }
                        close(fds[i].fd);
                        fds[i] = fds[nfds - 1];
                        nfds--;
                        i--;
                    }
                }
            }
        }
    }

    for (nfds_t i = 0; i < nfds; i++) {
        close(fds[i].fd);
    }
    return 0;
}
```

#### poll 优点

- 没有 `FD_SETSIZE` 这种固定上限。
- `pollfd` 数组比 `fd_set` 更直观。
- 可以为不同 fd 设置不同事件。
- POSIX 标准支持，可移植性仍然不错。

#### poll 缺点

- 每次调用仍要把整个数组传给内核。
- 返回后仍要线性扫描所有 fd。
- 当连接很多但活跃连接很少时，扫描成本明显。
- 数组增删需要自己管理。

---

### 3.4 epoll

#### 原理

`epoll` 是 Linux 特有的 I/O 事件通知机制，适合大量 fd 的场景。

它的基本使用流程：

```text
epoll_create1()
  |
epoll_ctl(ADD/MOD/DEL)
  |
epoll_wait()
  |
处理就绪事件
```

函数原型：

```c
#include <sys/epoll.h>

int epoll_create1(int flags);

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

int epoll_wait(int epfd,
               struct epoll_event *events,
               int maxevents,
               int timeout);
```

常见操作：

| 操作 | 说明 |
| --- | --- |
| `EPOLL_CTL_ADD` | 添加 fd 到 epoll 实例 |
| `EPOLL_CTL_MOD` | 修改 fd 关注的事件 |
| `EPOLL_CTL_DEL` | 从 epoll 实例删除 fd |

常见事件：

| 事件 | 说明 |
| --- | --- |
| `EPOLLIN` | 可读 |
| `EPOLLOUT` | 可写 |
| `EPOLLERR` | 错误 |
| `EPOLLHUP` | 挂起 |
| `EPOLLRDHUP` | 对端关闭写方向，常用于检测半关闭 |
| `EPOLLET` | 边缘触发模式 |
| `EPOLLONESHOT` | 事件触发一次后自动禁用，需要重新注册 |

与 `select` / `poll` 不同，`epoll` 把“关注哪些 fd”这个状态保存在内核中的 epoll 实例里。用户程序不需要每次调用 `epoll_wait` 都重新传入完整 fd 集合。

#### epoll 核心示例

下面是 TCP echo server 的完整 `epoll` 版本。这里使用非阻塞 socket 和 LT 模式，代码比 ET 模式更适合入门。

编译：

```bash
gcc -Wall -Wextra -O2 epoll_echo_server.c -o epoll_echo_server
```

运行：

```bash
./epoll_echo_server 8080
```

代码关键逻辑：

- `listen_fd` 和客户端 `conn_fd` 都设置为非阻塞。
- `listen_fd` 可读时，循环 `accept`，直到 `EAGAIN`。
- 客户端可读时，循环 `recv`，直到 `EAGAIN` 或对端关闭。
- 对端关闭或发生错误时，先从 epoll 删除，再关闭 fd。

```c
// epoll_echo_server.c
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_EVENTS 1024

static int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static int create_listen_socket(int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        perror("setsockopt");
        close(fd);
        exit(1);
    }

    if (set_nonblocking(fd) == -1) {
        perror("fcntl");
        close(fd);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((uint16_t)port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(fd);
        exit(1);
    }

    if (listen(fd, SOMAXCONN) == -1) {
        perror("listen");
        close(fd);
        exit(1);
    }

    return fd;
}

static int add_epoll_fd(int epfd, int fd, uint32_t events) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = events;
    ev.data.fd = fd;
    return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}

static void close_epoll_fd(int epfd, int fd) {
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    close(fd);
}

static int echo_once(int fd, const char *buf, ssize_t len) {
    ssize_t sent = 0;
    while (sent < len) {
        ssize_t n = send(fd, buf + sent, (size_t)(len - sent), 0);
        if (n > 0) {
            sent += n;
        } else if (n == -1 && errno == EINTR) {
            continue;
        } else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    signal(SIGPIPE, SIG_IGN);

    int listen_fd = create_listen_socket(atoi(argv[1]));
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd == -1) {
        perror("epoll_create1");
        close(listen_fd);
        return 1;
    }

    if (add_epoll_fd(epfd, listen_fd, EPOLLIN) == -1) {
        perror("epoll_ctl listen_fd");
        close(listen_fd);
        close(epfd);
        return 1;
    }

    struct epoll_event events[MAX_EVENTS];
    printf("epoll echo server listening on port %s\n", argv[1]);

    for (;;) {
        int nready = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (nready == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nready; i++) {
            int fd = events[i].data.fd;
            uint32_t ev = events[i].events;

            if (fd == listen_fd) {
                for (;;) {
                    struct sockaddr_in peer;
                    socklen_t peer_len = sizeof(peer);
                    int conn_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
                    if (conn_fd == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        }
                        if (errno == EINTR) {
                            continue;
                        }
                        perror("accept");
                        break;
                    }

                    if (set_nonblocking(conn_fd) == -1) {
                        perror("fcntl conn_fd");
                        close(conn_fd);
                        continue;
                    }

                    if (add_epoll_fd(epfd, conn_fd, EPOLLIN | EPOLLRDHUP) == -1) {
                        perror("epoll_ctl conn_fd");
                        close(conn_fd);
                        continue;
                    }
                }
                continue;
            }

            if (ev & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
                close_epoll_fd(epfd, fd);
                continue;
            }

            if (ev & EPOLLIN) {
                for (;;) {
                    char buf[4096];
                    ssize_t n = recv(fd, buf, sizeof(buf), 0);
                    if (n > 0) {
                        if (echo_once(fd, buf, n) == -1) {
                            close_epoll_fd(epfd, fd);
                            break;
                        }
                    } else if (n == 0) {
                        close_epoll_fd(epfd, fd);
                        break;
                    } else {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        }
                        if (errno == EINTR) {
                            continue;
                        }
                        perror("recv");
                        close_epoll_fd(epfd, fd);
                        break;
                    }
                }
            }
        }
    }

    close(listen_fd);
    close(epfd);
    return 0;
}
```

这个示例为了突出 `epoll` 读事件处理，把写事件处理简化了：如果 `send` 只发出一部分数据或返回 `EAGAIN`，生产级服务器应当把剩余数据放入连接的输出缓冲区，并注册 `EPOLLOUT`，等 socket 可写后继续发送。

#### epoll 优点

- 适合大量连接。
- 不需要每次把全部 fd 集合从用户态传入内核。
- `epoll_wait` 返回的是就绪事件数组，通常不需要扫描所有 fd。
- 支持 LT 和 ET 两种触发模式。
- 支持 `EPOLLONESHOT` 等更适合复杂事件循环的机制。

#### epoll 缺点

- Linux 特有，可移植性不如 `select` / `poll`。
- API 和状态管理更复杂。
- ET 模式对非阻塞和读写循环要求很严格，写错容易丢事件或卡住。
- 需要正确管理连接状态、输出缓冲区、超时、关闭等细节。

---

### 3.5 epoll 的 LT 和 ET 模式

`epoll` 有两种触发方式：

| 模式 | 名称 | 行为 |
| --- | --- | --- |
| LT | Level Triggered，水平触发 | 只要 fd 仍然处于就绪状态，`epoll_wait` 就会反复通知 |
| ET | Edge Triggered，边缘触发 | 只有 fd 状态从未就绪变为就绪时通知一次 |

#### LT 模式

LT 是默认模式，行为更像 `select` / `poll`：

```text
socket 接收缓冲区里有 100 字节
epoll_wait 返回可读
程序只读了 20 字节
缓冲区还剩 80 字节
下一次 epoll_wait 仍会返回可读
```

优点是简单，不容易因为一次没读完而丢事件。

#### ET 模式

ET 模式只在状态变化时通知：

```text
socket 接收缓冲区从空变为非空
epoll_wait 返回可读
程序只读了 20 字节
缓冲区还剩 80 字节
下一次 epoll_wait 不一定再通知
```

所以 ET 模式的基本要求是：

1. fd 必须设置为非阻塞。
2. 收到可读事件后，要循环 `recv`，直到返回 `EAGAIN` / `EWOULDBLOCK`。
3. 收到可写事件后，要循环 `send`，直到写完或返回 `EAGAIN` / `EWOULDBLOCK`。

典型 ET 读法：

```c
for (;;) {
    ssize_t n = recv(fd, buf, sizeof(buf), 0);
    if (n > 0) {
        // 处理数据
    } else if (n == 0) {
        // 对端关闭
        close(fd);
        break;
    } else {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            // 已经读到当前没有更多数据
            break;
        }
        if (errno == EINTR) {
            continue;
        }
        // 其他错误
        close(fd);
        break;
    }
}
```

ET 模式不是“天然更快”的魔法。它减少重复通知，但要求程序把每个事件处理到位。对大部分初学者和很多业务服务来说，先使用 LT 模式更稳妥。

---

## 4. 对比总结

### 4.1 select / poll / epoll 表格对比

| 维度 | select | poll | epoll |
| --- | --- | --- | --- |
| 标准/平台 | POSIX | POSIX | Linux 特有 |
| fd 集合表示 | `fd_set` 位图 | `struct pollfd` 数组 | 内核中的 epoll 实例 |
| fd 数量限制 | 受 `FD_SETSIZE` 影响 | 理论上不受固定数组宏限制 | 受系统资源和 fd 限制 |
| 每次调用是否传全部 fd | 是 | 是 | 否，fd 通过 `epoll_ctl` 维护 |
| 返回后是否要扫描全部 fd | 通常要从 `0` 扫到 `max_fd` | 通常要扫描整个数组 | 返回就绪事件数组 |
| 时间复杂度直观理解 | O(n) | O(n) | 活跃事件较少时更接近 O(ready) |
| 可移植性 | 好 | 好 | 差，仅 Linux |
| API 复杂度 | 低 | 中 | 中到高 |
| 典型场景 | 小规模、兼容性要求高 | 中小规模、兼容性要求高 | Linux 高并发网络服务 |

这里的复杂度是工程直观理解，不是严格算法证明。真实性能还会受到连接活跃度、数据量、系统调用频率、缓存局部性、应用逻辑等因素影响。

### 4.2 从性能角度

`select` 和 `poll` 的共同问题是：每次等待都要告诉内核“我要监听哪些 fd”，返回后还要在用户态找“到底哪些 fd 就绪了”。

当 fd 数量很大，但活跃 fd 很少时，这种线性扫描成本会很明显。

`epoll` 的优势在于：

- 监听集合由内核长期维护。
- 事件就绪后放入就绪队列。
- `epoll_wait` 返回的是就绪事件。

所以 Linux 上的高并发网络服务通常优先考虑 `epoll`。

### 4.3 从可移植性角度

| 机制 | 可移植性 |
| --- | --- |
| `select` | POSIX，广泛支持 |
| `poll` | POSIX，广泛支持 |
| `epoll` | Linux 特有 |

其他系统有类似机制：

- BSD/macOS：`kqueue`。
- Solaris：`/dev/poll`、event ports。
- Windows：IOCP。

跨平台网络库通常会在不同系统上选择不同后端。例如 libevent 在 Linux 上可用 `epoll`，在 BSD/macOS 上可用 `kqueue`。

### 4.4 从复杂度角度

| 机制 | 编程复杂度 | 主要复杂点 |
| --- | --- | --- |
| `select` | 低 | 重建 `fd_set`、维护 `max_fd`、处理 `FD_SETSIZE` |
| `poll` | 中 | 动态维护 `pollfd` 数组 |
| `epoll` | 中到高 | 非阻塞、事件注册/修改/删除、LT/ET、输出缓冲区 |

如果只是写一个教学 demo 或简单管理几十个 fd，`select` / `poll` 完全可以胜任。如果要写 Linux 上的高并发服务，`epoll` 更合适。

### 4.5 适用场景建议

| 场景 | 建议 |
| --- | --- |
| 教学、实验、小工具 | `select` 或 `poll` |
| 需要 POSIX 可移植性 | `poll` 通常比 `select` 更舒服 |
| Linux 高并发 TCP 服务 | `epoll` |
| 需要跨平台高性能 | 使用 libevent/libuv/Boost.Asio 等库 |
| 业务代码重点不在网络底层 | 使用成熟网络框架 |

---

## 5. 示例代码：从简单 echo server 到多路复用

前面已经给出了 `select`、`poll`、`epoll` 三个完整版本。这里再补一个最基础的阻塞 TCP echo server，帮助你对照理解。

### 5.1 最简单的阻塞 TCP echo server

这个版本一次只处理一个客户端。它的优点是流程非常清楚，缺点是当前客户端不退出时，其他客户端即使连接成功，也无法被应用层及时处理。

编译：

```bash
gcc -Wall -Wextra -O2 blocking_echo_server.c -o blocking_echo_server
```

运行：

```bash
./blocking_echo_server 8080
```

代码：

```c
// blocking_echo_server.c
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static int create_listen_socket(int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(1);
    }

    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        perror("setsockopt");
        close(fd);
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((uint16_t)port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(fd);
        exit(1);
    }

    if (listen(fd, SOMAXCONN) == -1) {
        perror("listen");
        close(fd);
        exit(1);
    }

    return fd;
}

static int echo_client(int conn_fd) {
    char buf[4096];
    for (;;) {
        ssize_t n = recv(conn_fd, buf, sizeof(buf), 0);
        if (n > 0) {
            ssize_t sent = 0;
            while (sent < n) {
                ssize_t m = send(conn_fd, buf + sent, (size_t)(n - sent), 0);
                if (m > 0) {
                    sent += m;
                } else if (m == -1 && errno == EINTR) {
                    continue;
                } else {
                    return -1;
                }
            }
        } else if (n == 0) {
            return 0;
        } else {
            if (errno == EINTR) {
                continue;
            }
            perror("recv");
            return -1;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    signal(SIGPIPE, SIG_IGN);

    int listen_fd = create_listen_socket(atoi(argv[1]));
    printf("blocking echo server listening on port %s\n", argv[1]);

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

        echo_client(conn_fd);
        close(conn_fd);
    }

    close(listen_fd);
    return 0;
}
```

### 5.2 四个版本的关系

| 版本 | 并发处理能力 | 编程重点 |
| --- | --- | --- |
| 阻塞版 | 最弱，一次主要服务一个客户端 | 理解 TCP server 流程 |
| `select` 版 | 可同时管理多个客户端 | 理解 fd 集合和事件等待 |
| `poll` 版 | 类似 `select`，fd 数量管理更灵活 | 理解数组式事件描述 |
| `epoll` 版 | 更适合大量连接 | 理解非阻塞和事件循环 |

如果你想把这些代码拆成真实 `.c` 文件，可以把对应代码块复制到文件中，例如 `epoll_echo_server.c`，然后用文中的 `gcc` 命令编译。

---

## 6. 常见坑

### 6.1 fd 泄漏

socket 是 fd，占用内核资源。常见泄漏场景：

- `accept` 得到 `conn_fd` 后，错误路径忘记 `close`。
- 从 `select` / `poll` / `epoll` 移除连接时，只删除事件，忘记关闭 fd。
- `fork` / `exec` 后子进程继承了不该继承的 fd。
- 多处代码都保存 fd，生命周期不清楚。

建议：

- 每个 fd 明确所有权。
- 出错路径统一清理。
- 使用 `EPOLL_CLOEXEC`、`SOCK_CLOEXEC` 或 `fcntl(fd, F_SETFD, FD_CLOEXEC)` 防止 exec 泄漏。
- 对长时间运行的服务，监控 fd 数量，例如查看 `/proc/<pid>/fd`。

---

### 6.2 半连接与 listen backlog

TCP 建立连接需要三次握手。服务端内核维护与监听 socket 相关的队列，常被粗略称为半连接队列和已完成连接队列。

容易误解的点：

- `listen(fd, backlog)` 不是应用层可同时处理的最大连接数。
- 如果应用层 `accept` 太慢，已完成连接队列可能积压。
- 如果 SYN 洪泛或网络异常，半连接队列可能承压。
- Linux 还会受 `net.core.somaxconn`、`net.ipv4.tcp_max_syn_backlog` 等系统参数影响。

生产服务里，`backlog`、worker 数量、`accept` 速度、系统参数要一起考虑。

---

### 6.3 TCP 粘包/拆包

TCP 是字节流，不是消息协议。

如果客户端这样发送：

```text
send("hello")
send("world")
```

服务端可能读到：

```text
"helloworld"
```

也可能读到：

```text
"he"
"llow"
"orld"
```

这不是 TCP 出错，而是 TCP 的正常行为。

应用层必须自己定义协议边界，常见做法：

- 固定长度消息。
- 分隔符协议，例如一行一个消息，以 `\n` 结尾。
- 长度前缀协议，例如前 4 字节表示后面消息体长度。

echo server 可以直接原样返回字节流，所以看起来不需要处理消息边界。但一旦写聊天、RPC、网关、数据库协议，就必须处理粘包/拆包。

---

### 6.4 SIGPIPE

当对端已经关闭连接，本端继续 `send`，进程可能收到 `SIGPIPE`。默认行为是终止进程。

常见处理方式：

```c
signal(SIGPIPE, SIG_IGN);
```

或者发送时使用 Linux 支持的 `MSG_NOSIGNAL`：

```c
send(fd, buf, len, MSG_NOSIGNAL);
```

如果不处理 `SIGPIPE`，服务器可能因为一个断开的客户端而直接退出。

---

### 6.5 epoll ET 模式下没有读到 EAGAIN

ET 模式最常见的问题是：收到一次可读事件后，只 `recv` 一次就返回事件循环。

错误示例：

```c
// ET 模式下不够
recv(fd, buf, sizeof(buf), 0);
```

如果 socket 缓冲区还有数据没读完，而之后没有新的边沿变化，`epoll_wait` 可能不会再次通知这个 fd。连接看起来就“卡住”了。

正确思路：

```c
for (;;) {
    ssize_t n = recv(fd, buf, sizeof(buf), 0);
    if (n > 0) {
        // 处理数据
        continue;
    }
    if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        break;
    }
    // 处理关闭或错误
    break;
}
```

ET 模式下，可读读到 `EAGAIN`，可写写到 `EAGAIN` 或写完，是基本纪律。

---

### 6.6 忘记设置非阻塞 fd

使用 `epoll`，尤其是 ET 模式时，忘记设置非阻塞非常危险。

假设你在 ET 模式中写了：

```c
for (;;) {
    recv(fd, buf, sizeof(buf), 0);
}
```

如果 fd 是阻塞的，当数据读完后，下一次 `recv` 会阻塞住，整个事件循环就停了。

所以高并发事件循环里通常会：

```c
set_nonblocking(listen_fd);
set_nonblocking(conn_fd);
```

并且所有 `accept`、`recv`、`send` 都要按非阻塞语义处理 `EAGAIN` / `EWOULDBLOCK`。

---

## 7. 学习路径建议

建议按这个顺序练习：

1. 先写阻塞 echo server 和 echo client，理解 `socket`、`bind`、`listen`、`accept`、`connect`、`send`、`recv`。
2. 把 server 改成 `select` 版本，理解“一个线程等多个 fd”。
3. 把 `select` 改成 `poll`，理解数组式管理。
4. 写 `epoll` LT 版本，理解事件注册和非阻塞 I/O。
5. 再尝试 `epoll` ET 版本，重点练习“读到 EAGAIN”。
6. 最后补上输出缓冲区、连接超时、协议拆包、日志和优雅关闭。

网络编程的难点不只在系统调用本身，而在“状态管理”：连接什么时候创建、什么时候可读、什么时候可写、什么时候半关闭、什么时候释放资源。把这些状态画清楚，socket 编程会顺很多。
