# 04. poll

`poll` 和 `select` 的目标类似：一个线程同时等待多个 fd 的事件。区别在于，`poll` 使用 `struct pollfd` 数组描述 fd，而不是 `fd_set`。

## 基本模型

```c
struct pollfd {
    int fd;
    short events;
    short revents;
};
```

字段含义：

| 字段 | 说明 |
| --- | --- |
| `fd` | 要监听的文件描述符 |
| `events` | 程序关心的事件 |
| `revents` | 内核返回的实际事件 |

函数原型：

```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

常见事件：

| 事件 | 说明 |
| --- | --- |
| `POLLIN` | 可读 |
| `POLLOUT` | 可写 |
| `POLLERR` | 错误 |
| `POLLHUP` | 对端挂起或连接关闭 |
| `POLLNVAL` | fd 无效 |

`events` 是你关心的事件，`revents` 是内核实际返回的事件。某些错误类事件即使你没有放进 `events`，也可能出现在 `revents` 中。例如 `POLLERR`、`POLLHUP`、`POLLNVAL` 都应该检查。

`POLLHUP` 也不等于“马上丢掉 fd”。它可能和 `POLLIN` 同时出现，表示对端关闭了，但接收缓冲区里还有剩余数据。稳妥做法是：如果还有 `POLLIN`，先把数据读完，再根据 `recv` 返回值关闭。

## 本章代码

`poll_echo_server.c` 是一个单线程 TCP echo server。

运行：

```bash
./build/poll_echo_server 8080
```

测试：

```bash
nc 127.0.0.1 8080
```

## 代码结构

本示例使用：

```c
struct pollfd fds[MAX_CLIENTS + 1];
nfds_t nfds;
```

`fds[0]` 固定保存监听 socket。新客户端连接后，把它追加到数组尾部。

删除客户端 fd 时，用数组最后一个元素覆盖当前位置：

```c
fds[i] = fds[nfds - 1];
nfds--;
```

这样可以避免数组中间出现空洞。

还可以把某个 `pollfd.fd` 设置为负数，`poll` 会忽略这一项。这适合临时禁用某个 fd，但如果数组长期很大，还是会产生线性扫描成本。

## 写事件与背压

和 `select` 一样，`POLLOUT` 不能一直监听。大多数空闲 TCP 连接通常都是可写的，一直监听会导致 `poll` 反复返回。

更合理的模式是：

```text
没有待发送数据：只监听 POLLIN
send 出现短写：保存剩余数据，增加 POLLOUT
待发送数据写完：移除 POLLOUT
```

这就是“输出缓冲区”和“背压”的开始。`epoll_buffered_echo_server.c` 里会用同样思想做一个更完整的例子。

## 优点

- POSIX 接口，可移植性好。
- 没有 `FD_SETSIZE` 这种固定 fd 集合限制。
- `pollfd` 数组比 `fd_set` 更清楚地表达事件。

## 缺点

- 每次调用仍要把整个数组传给内核。
- 返回后仍要线性扫描整个数组。
- fd 很多、活跃 fd 很少时效率不理想。

## poll 相比 select 的真实优势

`poll` 最重要的改善不是“性能飞跃”，而是接口形态更适合动态 fd：

- 不需要维护 `max_fd`。
- 不受 `FD_SETSIZE` 位图大小影响。
- 每个 fd 的关心事件和返回事件都在同一个结构体里。

但它依然是“每次传入一整个数组、返回后线性扫描一整个数组”。因此在大规模连接上，它和 `epoll` 的差距来自模型本身。
