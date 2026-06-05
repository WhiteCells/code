# 06. 对比总结与常见坑

## select / poll / epoll 对比

| 维度 | select | poll | epoll |
| --- | --- | --- | --- |
| 标准/平台 | POSIX | POSIX | Linux 特有 |
| fd 表示方式 | `fd_set` | `struct pollfd` 数组 | 内核中的 epoll 实例 |
| fd 数量限制 | 受 `FD_SETSIZE` 影响 | 受数组大小和系统资源限制 | 受系统资源和 fd 限制 |
| 每次是否传全部 fd | 是 | 是 | 否 |
| 返回后是否扫描全部 fd | 通常要 | 通常要 | 通常只遍历就绪事件 |
| 编程复杂度 | 低 | 中 | 中到高 |
| 可移植性 | 好 | 好 | 仅 Linux |
| 适用场景 | 少量 fd、小工具、教学 | 中小规模、需要 POSIX | Linux 高并发服务 |

更关键的区别不是某个系统调用本身快几个纳秒，而是三者的状态模型不同：

| 机制 | 状态放在哪里 | 每次等待前要做什么 |
| --- | --- | --- |
| `select` | 用户态 `fd_set` | 重建集合，传入内核 |
| `poll` | 用户态 `pollfd` 数组 | 更新数组，传入内核 |
| `epoll` | 内核 epoll 实例 | 只在 fd 状态变化时 `epoll_ctl` |

## 性能角度

`select` 和 `poll` 都有线性扫描成本。当监听 fd 很多但活跃 fd 很少时，这种成本会比较明显。

`epoll` 把监听集合保存在内核中，通过 `epoll_ctl` 增删改。`epoll_wait` 返回就绪事件数组，因此更适合大量连接。

## 可移植性角度

- `select`：POSIX，广泛支持。
- `poll`：POSIX，广泛支持。
- `epoll`：Linux 特有。

其他平台有自己的高性能事件机制：

- BSD/macOS：`kqueue`。
- Windows：IOCP。

跨平台网络库通常会根据平台选择不同后端，比如 libevent、libuv、Boost.Asio。

## 常见坑

本目录的 `length_prefixed_codec_demo.c` 演示一种常见的 TCP 消息边界处理方式：长度前缀协议。它不是完整网络服务器，而是把多条消息编码成连续字节流，再从字节流中逐条解码，帮助理解为什么 TCP 应用层需要自己处理粘包/拆包。

运行：

```bash
./build/length_prefixed_codec_demo
```

### fd 泄漏

每个 socket 都是 fd。错误路径、连接关闭路径、从事件循环移除 fd 的路径都要注意 `close`。

典型建议：

- `accept` 成功后，后续失败要关闭 `conn_fd`。
- 从 `epoll` 删除 fd 后也要 `close`。
- 使用 `EPOLL_CLOEXEC`、`SOCK_CLOEXEC` 或 `FD_CLOEXEC` 防止 exec 后泄漏。

生产服务还要考虑 `EMFILE`：进程 fd 数达到 `ulimit -n` 后，`accept` 会失败。常见做法是提高 fd 限制，并在服务里监控 fd 使用量。更高级的实现会保留一个 emergency fd，遇到 `EMFILE` 时临时关闭它、`accept` 一个连接并关闭，再重新打开 emergency fd，避免监听 socket 一直处于不可恢复状态。

### listen backlog 不是最大并发数

`listen(fd, backlog)` 影响监听 socket 的连接队列，但不是应用层最大并发连接数的简单等价物。

实际效果还会受到：

- 应用层 `accept` 速度。
- `net.core.somaxconn`。
- `net.ipv4.tcp_max_syn_backlog`。
- worker 数量和调度情况。

TCP 连接建立大致涉及两个队列：

| 队列 | 粗略含义 |
| --- | --- |
| SYN 队列 | 收到 SYN、握手尚未完全完成的连接 |
| accept 队列 | 三次握手完成、等待应用 `accept` 的连接 |

`listen(backlog)` 主要影响已完成连接队列的容量上限，但 Linux 会结合系统参数做限制。应用层 `accept` 太慢时，客户端可能连接超时、重传，甚至被拒绝。

### TCP 粘包/拆包

TCP 是字节流，不保留消息边界。

客户端连续发送：

```text
"hello"
"world"
```

服务端可能一次读到：

```text
"helloworld"
```

也可能分多次读到：

```text
"he"
"llow"
"orld"
```

应用层必须自己定义协议边界，例如固定长度、分隔符、长度前缀。

长度前缀协议常见格式：

```text
4 字节网络序长度 + N 字节消息体
```

解析时不能假设一次 `recv` 得到完整包。通常要维护输入缓冲区：

```text
recv 到多少就追加多少
  |
缓冲区不足 4 字节：继续等
  |
读出长度字段
  |
缓冲区不足完整 body：继续等
  |
取出一条完整消息并处理
```

`length_prefixed_codec_demo.c` 演示的是这个思路的最小版本。

### SIGPIPE

对端关闭后，本端继续 `send` 可能触发 `SIGPIPE`，默认行为是终止进程。

常见处理：

```c
signal(SIGPIPE, SIG_IGN);
```

或者 Linux 下发送时使用：

```c
send(fd, buf, len, MSG_NOSIGNAL);
```

忽略 `SIGPIPE` 后，断开连接上的 `send` 通常会返回 `-1`，`errno` 为 `EPIPE`。这时要按普通连接错误关闭 fd。

### 短写和输出缓冲

一次 `send` 不保证写完所有数据。即使 socket 可写，也可能只写入一部分。

错误思路：

```c
send(fd, buf, len, 0);
// 默认 len 都发完了
```

正确思路：

```text
send 返回 n
  |
n < len：把剩余数据保存到输出缓冲区
  |
注册 POLLOUT/EPOLLOUT
  |
可写后继续发送
  |
发送完再取消写事件
```

如果输出缓冲越积越多，说明对端读得慢。服务端必须选择策略：限制缓冲、暂停读取、丢弃连接，或者按业务优先级降级。

### 半关闭不是普通关闭

TCP 是全双工协议。一端可以关闭写方向，但继续读：

```c
shutdown(fd, SHUT_WR);
```

对端会读到 EOF，但仍可能继续发送数据。代理程序、隧道程序、上传后等待响应的协议里，半关闭处理错了会导致数据被提前截断。

### TIME_WAIT 和端口复用

主动关闭 TCP 连接的一方通常会进入 `TIME_WAIT`。这是 TCP 为了处理迟到报文和连接四元组复用而设计的状态，不是 bug。

服务端重启时常用 `SO_REUSEADDR`，这样可以更容易重新绑定监听端口。但它不是“随便复用任何连接”的开关。Linux 上还有 `SO_REUSEPORT`，它允许多个 socket 绑定同一地址端口，常用于多进程负载分担，语义和 `SO_REUSEADDR` 不一样。

### epoll ET 模式没有读到 EAGAIN

ET 模式下，收到可读事件后必须循环读取，直到：

```c
errno == EAGAIN || errno == EWOULDBLOCK
```

如果只读一次，缓冲区里剩余的数据可能不会再次触发通知，连接看起来会卡住。

写方向同理：ET 模式收到 `EPOLLOUT` 后，如果还有待发送数据，就要尽量写到 `EAGAIN` 或写完。否则剩余数据可能长期留在用户态输出缓冲区。

### 忘记设置非阻塞 fd

`epoll`，尤其 ET 模式，必须配合非阻塞 fd。否则事件循环可能在某个 `accept`、`recv` 或 `send` 上卡死。

典型做法：

```c
set_nonblocking(listen_fd);
set_nonblocking(conn_fd);
```

然后所有 I/O 都要正确处理 `EAGAIN` / `EWOULDBLOCK`。

### HUP/ERR 事件处理顺序

`EPOLLHUP` / `POLLHUP` 可能和可读事件一起返回。不要一看到 HUP 就直接关闭，否则可能丢掉接收缓冲区里最后的数据。

更稳妥的顺序：

```text
如果有 IN：先 recv 到 EAGAIN 或 EOF
如果有 OUT：尝试 flush 输出缓冲
如果有 HUP/ERR/RDHUP：标记连接准备关闭
输出缓冲清空后释放连接
```

## 实战建议

学习时可以按这个顺序：

1. 阻塞 TCP echo server/client。
2. UDP echo server/client。
3. 非阻塞 `accept` demo。
4. `select` echo server。
5. `poll` echo server。
6. `epoll` LT echo server。
7. 尝试给 `epoll` 版本加入输出缓冲区和 `EPOLLOUT`。

真正写业务服务时，底层细节很多，建议使用成熟网络库或框架。但理解这些系统调用，可以让你知道框架内部到底在做什么。
