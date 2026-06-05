# common：共享网络工具函数

这个目录放各章节示例共用的小工具函数，避免每个 demo 都重复写监听 socket 创建、非阻塞设置和完整发送逻辑。

## 文件

| 文件 | 说明 |
| --- | --- |
| `net_utils.h` | 工具函数声明 |
| `net_utils.c` | 工具函数实现 |

## 主要函数

```c
int create_tcp_server_socket(int port, int nonblocking);
int create_tcp_client_socket(const char *ip, int port);
int create_udp_server_socket(int port);
int set_nonblocking(int fd);
int send_all(int fd, const void *buf, size_t len);
void ignore_sigpipe(void);
```

## 设计目的

教程代码的重点是 socket 模型、阻塞/非阻塞 I/O，以及 `select` / `poll` / `epoll`。共享函数把重复的准备工作收拢起来，让每章源码更容易看出核心逻辑。

例如 `create_tcp_server_socket` 内部完成：

```text
socket -> setsockopt(SO_REUSEADDR) -> bind -> listen
```

如果传入 `nonblocking = 1`，它还会调用 `set_nonblocking`，适合 `epoll` 或非阻塞 demo 使用。
