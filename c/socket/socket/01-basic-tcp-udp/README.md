# 01. socket 基础：TCP 与 UDP

socket 是网络通信中的文件描述符。创建 socket 之后，程序可以通过系统调用在网络上收发数据，就像通过 fd 读写文件一样。

更准确地说，socket fd 是用户态访问内核 socket 对象的句柄。这个内核对象里有协议状态、接收缓冲区、发送缓冲区、本地地址、对端地址等信息。程序调用 `send` 时，数据通常先进入内核发送缓冲区；调用 `recv` 时，程序从内核接收缓冲区取数据。

## TCP socket

TCP 使用 `SOCK_STREAM`：

```c
int fd = socket(AF_INET, SOCK_STREAM, 0);
```

它的特点：

- 面向连接。
- 可靠传输。
- 保证顺序。
- 字节流，不保留消息边界。

TCP server 基本流程：

```text
socket -> bind -> listen -> accept -> recv/send -> close
```

TCP client 基本流程：

```text
socket -> connect -> send/recv -> close
```

本目录包含：

- `tcp_echo_server.c`：最简单的阻塞 TCP echo server。
- `tcp_echo_client.c`：连接服务器，发送一行数据并读取回复。
- `syscall-details.md`：更细的系统调用返回值、errno、socket 选项说明。

## TCP 调用细节

### `bind` 绑定的是本地地址

服务端常用：

```c
addr.sin_addr.s_addr = htonl(INADDR_ANY);
addr.sin_port = htons(8080);
```

`INADDR_ANY` 表示监听本机所有网卡地址。端口必须用 `htons` 转成网络字节序。客户端通常不用显式 `bind`，内核会自动选择本地 IP 和临时端口。

### `listen` 之后才是监听 socket

`listen_fd` 只负责等待连接。`accept` 返回的新 fd 才代表某个具体 TCP 连接：

```text
listen_fd: 服务端端口上的监听入口
conn_fd:   与某个客户端的一条 TCP 连接
```

不要在 `listen_fd` 上 `recv` 业务数据，也不要把 `conn_fd` 当成还能 `accept` 的 fd。

### `send` 成功不等于对端已经收到

`send` 返回成功，通常只表示数据被复制进了本机内核发送缓冲区，或者至少复制了一部分。它不表示对端应用已经 `recv` 到，也不表示对端已经处理完。

返回值必须检查：

| 返回值 | 含义 |
| --- | --- |
| `> 0` | 实际写入内核发送缓冲区的字节数 |
| `-1` | 出错或暂时不能写，检查 `errno` |

一次 `send` 可能只写入一部分数据，也就是短写。真实服务端需要维护“还没发完的数据”。

### `recv` 读的是字节流

TCP 不保留消息边界。一次 `recv` 读到多少字节，只取决于内核缓冲区当前数据、你的缓冲区大小、socket 状态等因素。它和对端调用了几次 `send` 没有一一对应关系。

`recv` 返回值：

| 返回值 | 含义 |
| --- | --- |
| `> 0` | 读取到的字节数 |
| `0` | 对端执行了有序关闭，本端读到了 EOF |
| `-1` | 出错或暂时不能读，检查 `errno` |

### `close` 与 `shutdown`

`close(fd)` 是关闭本进程里的 fd 引用。如果这是最后一个引用，内核会开始释放连接资源。TCP 连接层面通常会发送 FIN，但具体行为还受未发送数据、`SO_LINGER` 等影响。

`shutdown(fd, SHUT_WR)` 只关闭写方向，表示“我不再发送数据”，但仍然可以继续 `recv` 对端数据。这叫半关闭。HTTP/1.0、代理、隧道类程序里经常需要理解半关闭。

## UDP socket

UDP 使用 `SOCK_DGRAM`：

```c
int fd = socket(AF_INET, SOCK_DGRAM, 0);
```

它的特点：

- 无连接。
- 不保证可靠到达。
- 不保证顺序。
- 保留数据报边界。

UDP server 常用：

```text
socket -> bind -> recvfrom/sendto -> close
```

UDP client 常用：

```text
socket -> sendto/recvfrom -> close
```

本目录包含：

- `udp_echo_server.c`：UDP echo server。
- `udp_echo_client.c`：发送一条 UDP 消息并读取回复。

## 编译和运行

在上级 `socket-tutorial` 目录运行：

```bash
make
```

运行 TCP server：

```bash
./build/tcp_echo_server 8080
```

运行 TCP client：

```bash
./build/tcp_echo_client 127.0.0.1 8080 "hello tcp"
```

运行 UDP server：

```bash
./build/udp_echo_server 8081
```

运行 UDP client：

```bash
./build/udp_echo_client 127.0.0.1 8081 "hello udp"
```

## 关键观察

TCP echo server 里，`listen_fd` 只负责接收新连接，`accept` 返回的 `conn_fd` 才负责和某个客户端通信。

UDP server 没有 `listen` 和 `accept`。它用 `recvfrom` 一次读取一个数据报，同时拿到发送方地址，然后用 `sendto` 发回去。

UDP 的一个重要细节是：如果接收缓冲区太小，过长的数据报会被截断，剩余部分不会像 TCP 那样留给下一次读取。UDP 保留消息边界，但不保证可靠性。

UDP 也可以调用 `connect`。这不会建立 TCP 那样的连接，而是给 UDP socket 设置默认对端，并让内核过滤其他来源的数据。之后可以用 `send` / `recv`，错误处理也会更接近“有默认对端”的语义。
