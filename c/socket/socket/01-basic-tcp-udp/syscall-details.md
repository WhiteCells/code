# 系统调用细节速查

这一页专门补充 socket 编程里容易被一句话带过、但实际写代码时很关键的细节。

## socket

```c
int socket(int domain, int type, int protocol);
```

常见组合：

| domain | type | protocol | 含义 |
| --- | --- | --- | --- |
| `AF_INET` | `SOCK_STREAM` | `0` | IPv4 TCP |
| `AF_INET` | `SOCK_DGRAM` | `0` | IPv4 UDP |
| `AF_INET6` | `SOCK_STREAM` | `0` | IPv6 TCP |
| `AF_UNIX` | `SOCK_STREAM` | `0` | 本机 Unix domain stream socket |

Linux 可以在 `type` 里直接加：

```c
SOCK_NONBLOCK | SOCK_CLOEXEC
```

例如：

```c
socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
```

这样可以避免先创建 fd、再 `fcntl` 设置属性之间的竞态。

## setsockopt

常用选项：

| 选项 | 说明 |
| --- | --- |
| `SO_REUSEADDR` | 服务重启时更容易重新绑定端口 |
| `SO_REUSEPORT` | Linux 支持多个 socket 绑定同一地址端口，常用于多进程负载分担 |
| `SO_KEEPALIVE` | 开启 TCP keepalive，检测长时间空闲连接 |
| `TCP_NODELAY` | 关闭 Nagle 算法，降低小包延迟 |
| `SO_RCVBUF` / `SO_SNDBUF` | 设置接收/发送缓冲区大小 |
| `SO_LINGER` | 控制 `close` 时未发送数据的处理方式 |

`SO_REUSEADDR` 和 `SO_REUSEPORT` 不是同一个东西。前者常用于处理重启绑定问题，后者更像“多个监听 socket 共同接收连接”的机制。

## bind

`bind` 失败常见原因：

| errno | 常见含义 |
| --- | --- |
| `EADDRINUSE` | 地址端口已经被占用，或旧连接状态影响绑定 |
| `EACCES` | 权限不足，例如普通用户绑定 1024 以下端口 |
| `EADDRNOTAVAIL` | 要绑定的本地 IP 不属于本机 |

服务端常用 `INADDR_ANY`：

```c
addr.sin_addr.s_addr = htonl(INADDR_ANY);
```

如果只想监听本机回环地址，使用：

```c
inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
```

## listen

```c
int listen(int sockfd, int backlog);
```

`backlog` 不是最大连接数。它影响已完成连接队列的长度上限，并会被系统参数限制。

Linux 上可查看：

```bash
sysctl net.core.somaxconn
sysctl net.ipv4.tcp_max_syn_backlog
```

应用层如果 `accept` 太慢，即使 backlog 很大也可能出问题。

## accept / accept4

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

`accept` 返回的是新的连接 fd。监听 fd 继续保留，用于接受后续连接。

Linux 推荐使用 `accept4` 一次性设置属性：

```c
int conn_fd = accept4(listen_fd, NULL, NULL,
                      SOCK_NONBLOCK | SOCK_CLOEXEC);
```

这样可以避免 `accept` 后到 `fcntl` 前这段时间的竞态。

非阻塞监听 socket 上，连接队列为空时：

```text
accept -> -1, errno = EAGAIN/EWOULDBLOCK
```

这表示当前已经取完了可接受连接。

## connect

阻塞 socket 上，`connect` 通常等到成功或失败才返回。

非阻塞 socket 上：

```text
connect -> -1, errno = EINPROGRESS
```

表示连接正在建立。等待可写事件后，必须检查：

```c
int err = 0;
socklen_t len = sizeof(err);
getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &len);
```

`err == 0` 才表示连接成功。否则 `err` 是真实错误码。

## send / recv

`send` 可能短写：

```text
想发送 4096 字节
send 返回 1200
剩余 2896 字节必须以后继续发送
```

`recv` 可能短读：

```text
协议要求 4 字节长度字段
recv 可能只返回 1 或 2 字节
```

所以网络程序经常需要输入缓冲区和输出缓冲区。

常见 `errno`：

| errno | 说明 |
| --- | --- |
| `EINTR` | 被信号中断，通常可重试 |
| `EAGAIN` / `EWOULDBLOCK` | 非阻塞 fd 暂时不能读写 |
| `ECONNRESET` | 对端复位连接 |
| `EPIPE` | 对端已关闭，本端继续写 |
| `ETIMEDOUT` | 连接超时 |

## close / shutdown

`close` 关闭 fd 引用。`shutdown` 关闭连接的一个方向：

| 调用 | 含义 |
| --- | --- |
| `shutdown(fd, SHUT_RD)` | 关闭读方向 |
| `shutdown(fd, SHUT_WR)` | 关闭写方向，发送 FIN |
| `shutdown(fd, SHUT_RDWR)` | 关闭读写方向 |

如果你正在写代理，A 端 EOF 后通常不是立刻关闭 B 端 fd，而是：

```text
A 读到 EOF
  |
shutdown(B, SHUT_WR)
  |
继续把 B 的剩余数据转回 A
```

这就是半关闭语义。
