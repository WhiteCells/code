# 05. epoll

`epoll` 是 Linux 特有的 I/O 事件通知机制。它适合大量连接、少量连接活跃的网络服务。

## 基本模型

```text
epoll_create1()
  |
epoll_ctl(ADD/MOD/DEL)
  |
epoll_wait()
  |
处理就绪事件
```

常用函数：

```c
int epoll_create1(int flags);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

`epoll` 和 `select` / `poll` 的关键区别是：监听集合保存在内核里的 epoll 实例中。程序通过 `epoll_ctl` 增删改 fd，调用 `epoll_wait` 时只等待并取回就绪事件。

可以把 epoll 实例粗略理解成两部分：

| 概念 | 说明 |
| --- | --- |
| interest list | 你通过 `epoll_ctl` 注册进去的 fd 和事件 |
| ready list | 内核发现已经就绪、等待 `epoll_wait` 取走的事件 |

真实内核实现比这个更复杂，但这个模型足够解释大部分行为：`epoll_wait` 不需要你每次传入所有 fd，它只从 ready list 中取就绪事件。

## 常见事件

| 事件 | 说明 |
| --- | --- |
| `EPOLLIN` | 可读 |
| `EPOLLOUT` | 可写 |
| `EPOLLERR` | 错误 |
| `EPOLLHUP` | 挂起 |
| `EPOLLRDHUP` | 对端关闭写方向 |
| `EPOLLET` | 边缘触发 |
| `EPOLLONESHOT` | 事件触发一次后自动禁用 |

`EPOLLERR` 和 `EPOLLHUP` 有个重要细节：即使你没有显式注册，它们也可能被返回。处理事件时不要只判断 `EPOLLIN` / `EPOLLOUT`，错误和关闭事件也要纳入状态机。

`epoll_event.data` 很重要。简单 demo 常用：

```c
ev.data.fd = fd;
```

真实服务更常用：

```c
ev.data.ptr = connection;
```

这样事件返回时可以直接拿到连接状态，包括输入缓冲、输出缓冲、协议解析状态、最后活跃时间等。

## LT 与 ET

`epoll` 默认是 LT 模式。

| 模式 | 含义 | 行为 |
| --- | --- | --- |
| LT | 水平触发 | 只要 fd 仍然可读/可写，就会反复通知 |
| ET | 边缘触发 | 只在状态从未就绪变为就绪时通知 |

LT 示例：

```text
缓冲区有 100 字节
读了 20 字节
还剩 80 字节
下次 epoll_wait 还会提示可读
```

ET 示例：

```text
缓冲区从空变为非空时通知一次
如果只读 20 字节，剩余 80 字节不一定再次触发通知
```

所以 ET 模式必须：

- fd 设置为非阻塞。
- 可读时循环 `recv` 到 `EAGAIN` / `EWOULDBLOCK`。
- 可写时循环 `send` 到写完或 `EAGAIN` / `EWOULDBLOCK`。

LT 模式虽然宽容，也不代表可以忽略非阻塞。高并发服务里推荐监听 fd 和连接 fd 都设置非阻塞，因为：

- `accept` 可能一次事件对应多个连接，需要循环接受到 `EAGAIN`。
- `recv` 和 `send` 仍可能遇到竞态或短读短写。
- 如果某个调用意外阻塞，整个事件循环都会停住。

## 本章代码

本章有两个 epoll server：

| 文件 | 说明 |
| --- | --- |
| `epoll_echo_server.c` | 入门版，展示非阻塞 `accept` / `recv` 和 LT 模式 |
| `epoll_buffered_echo_server.c` | 进阶版，展示连接结构、输出缓冲、短写、动态 `EPOLLOUT` |

运行：

```bash
./build/epoll_echo_server 8080
```

运行进阶版：

```bash
./build/epoll_buffered_echo_server 8080
```

测试：

```bash
nc 127.0.0.1 8080
```

代码中有几个关键循环：

- `listen_fd` 可读时，循环 `accept`，直到 `EAGAIN`。
- `conn_fd` 可读时，循环 `recv`，直到 `EAGAIN` 或连接关闭。
- 关闭连接时，从 epoll 删除 fd 并 `close`。

这个示例把写事件简化了。如果 `send` 只写了一部分或返回 `EAGAIN`，生产级服务器应该把剩余数据放入连接的输出缓冲区，注册 `EPOLLOUT`，等可写后继续发送。

`epoll_buffered_echo_server.c` 就是在补这个洞。它的核心结构是：

```c
struct connection {
    int fd;
    int want_close;
    size_t out_sent;
    size_t out_len;
    char out[OUT_CAP];
};
```

关键规则：

- 读到数据后，不假设能马上发完，而是追加到 `out`。
- 每次尝试 `send`，只移动 `out_sent`。
- 待发送数据没写完时，注册 `EPOLLOUT`。
- 写完后，移除 `EPOLLOUT`，避免事件循环空转。
- 输出缓冲积压太多时，暂时不监听 `EPOLLIN`，让 TCP 反压客户端。

这才是事件驱动服务端真正绕不开的部分：不是“fd 可读就读，fd 可写就写”这么简单，而是要维护每条连接在读方向、写方向、关闭方向上的状态。

## epoll_ctl 的时机

常见模式：

| 时机 | 操作 |
| --- | --- |
| 新连接建立 | `EPOLL_CTL_ADD`，通常监听 `EPOLLIN` |
| 产生待发送数据 | `EPOLL_CTL_MOD`，增加 `EPOLLOUT` |
| 待发送数据清空 | `EPOLL_CTL_MOD`，移除 `EPOLLOUT` |
| 连接关闭 | `EPOLL_CTL_DEL`，然后 `close` |

关闭 fd 时，Linux 会把它从 epoll 实例中移除，但代码里仍建议显式 `EPOLL_CTL_DEL`，这样资源生命周期更清楚。尤其是存在 `dup`、多线程、复杂所有权时，不要靠隐式行为猜测。

## EPOLLONESHOT 和多线程

如果多个 worker 线程同时 `epoll_wait` 同一个 epoll 实例，同一个 fd 的事件可能被多个线程并发处理。常见解决方式是使用 `EPOLLONESHOT`：

```text
事件触发一次
  |
内核暂时禁用该 fd 的事件
  |
某个线程独占处理
  |
处理完成后 EPOLL_CTL_MOD 重新启用
```

这不是入门 echo server 必需的，但真实多线程 reactor 里很常见。

## 优点

- 大量连接时性能更适合 Linux 服务端。
- 返回的是就绪事件数组，不需要扫描全部 fd。
- 支持 LT、ET、`EPOLLONESHOT` 等机制。

## 缺点

- Linux 特有，不是 POSIX。
- 状态管理复杂。
- ET 模式容易因为没有读到 `EAGAIN` 而卡住。

## epoll 常见误解

| 误解 | 更准确的说法 |
| --- | --- |
| epoll 一定比 poll 快 | 大量 fd、少量活跃时优势明显；小规模场景差距可能不重要 |
| 可写事件应该一直开 | 只在有待发送数据时开，否则容易空转 |
| ET 模式一定更高性能 | ET 减少重复通知，但代码复杂度和 bug 风险更高 |
| HUP/ERR 可以最后再管 | HUP/ERR 可能和 IN 同时出现，应进入连接状态机处理 |
| close fd 就万事大吉 | 复杂所有权下要明确从 epoll 删除并释放连接状态 |
