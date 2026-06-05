# 02. 阻塞与非阻塞 I/O

默认创建出来的 socket 通常是阻塞的。阻塞 socket 上，如果操作暂时无法完成，调用线程会睡眠等待。

典型行为：

| 调用 | 阻塞条件 |
| --- | --- |
| `accept` | 没有新连接 |
| `recv` | 没有数据可读 |
| `send` | 发送缓冲区满 |
| `connect` | 连接还没有建立或失败 |

阻塞 I/O 写起来简单，但高并发时成本很高。如果一个线程阻塞在某个慢连接上，它就不能处理其他连接。

阻塞不只是“等待数据”。`send` 也可能阻塞：当对端读得很慢、本机发送缓冲区被占满时，阻塞 socket 上的 `send` 会卡住。很多初学代码只考虑 `recv` 会阻塞，忽略了写方向也会把整个线程拖住。

## 非阻塞 socket

非阻塞 socket 遇到“暂时不能完成”的情况会立即返回：

- 没有新连接时，非阻塞 `accept` 返回 `-1`。
- 没有数据时，非阻塞 `recv` 返回 `-1`。
- 发送缓冲区满时，非阻塞 `send` 返回 `-1`。

此时 `errno` 通常是：

```c
EAGAIN 或 EWOULDBLOCK
```

它们的含义是：现在做不了，请稍后再试。这不是连接断开，也不是致命错误。

需要同时判断两个宏：

```c
if (errno == EAGAIN || errno == EWOULDBLOCK) {
    // 等待下一次可读/可写事件
}
```

Linux 上这两个值通常相同，但可移植代码不应该依赖这一点。

## 设置非阻塞

本项目在 `common/net_utils.c` 中提供了：

```c
int set_nonblocking(int fd);
```

核心做法是：

```c
int flags = fcntl(fd, F_GETFL, 0);
fcntl(fd, F_SETFL, flags | O_NONBLOCK);
```

`O_NONBLOCK` 是 fd 对应打开文件描述状态的一部分。通过 `dup` 复制出来的 fd 通常共享这份状态，所以一个 fd 设置非阻塞，另一个复制 fd 也可能受到影响。多线程或 `fork` 后共享 fd 时要特别小心。

## readiness 不等于操作一定完成

`select` / `poll` / `epoll` 返回“可读”或“可写”，只表示这次操作大概率不会阻塞，并不保证你想读写的全部数据都能完成。

典型例子：

- 多个线程同时读同一个 fd，一个线程看到可读，另一个线程先把数据读走了。
- socket 可写，只说明发送缓冲区有一些空间，不代表你的 1 MB 数据能一次全部写进去。
- 可读事件到来后，`recv` 仍可能因为竞态、信号、协议状态变化返回错误。

所以事件循环里仍然必须处理：

```text
短读、短写、EINTR、EAGAIN/EWOULDBLOCK、0 字节 EOF
```

## 非阻塞 connect

非阻塞客户端连接服务器时，`connect` 常见返回：

```text
-1, errno = EINPROGRESS
```

这表示连接正在进行中，不是失败。后续通常监听可写事件，然后用 `getsockopt` 检查最终结果：

```c
int err = 0;
socklen_t len = sizeof(err);
getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &len);
if (err == 0) {
    // 连接成功
} else {
    // err 是真实连接错误，例如 ECONNREFUSED
}
```

只看到“可写”还不够，必须读取 `SO_ERROR`。

## 为什么不能忙轮询

非阻塞不是让程序这样写：

```c
for (;;) {
    recv(fd, buf, sizeof(buf), 0);
}
```

如果没有数据，这会让 CPU 空转。正确做法是：没有数据时遇到 `EAGAIN`，把 fd 交给 I/O 多路复用机制，等下一次事件通知。

## 本章代码

`nonblocking_accept_demo.c` 展示了非阻塞监听 socket 的行为：

1. 创建 TCP server socket，并设置为非阻塞。
2. 循环调用 `accept`。
3. 没有连接时打印 `EAGAIN/EWOULDBLOCK`。
4. 有客户端连接时正常接收并立即关闭。

运行：

```bash
./build/nonblocking_accept_demo 8080
```

另开终端连接：

```bash
nc 127.0.0.1 8080
```

你会看到程序在没有连接时不会卡死，而是不断得到“暂时没有连接”的状态。

## 为什么高并发服务需要非阻塞 I/O

高并发服务通常不希望一个线程卡在某个 fd 上。更常见的模型是：

```text
所有 fd 设置为非阻塞
  |
用 select / poll / epoll 等待事件
  |
事件来了再 accept/recv/send
  |
处理到 EAGAIN 后回到事件循环
```

这个模型让少量线程管理大量连接，避免大量线程阻塞等待。
