# 03. select

`select` 是经典的 I/O 多路复用接口。它解决的问题是：一个线程如何同时等待多个 fd 的可读、可写或异常事件。

## 基本模型

```text
准备 fd_set
  |
调用 select
  |
select 返回已经就绪的 fd
  |
遍历 fd_set，处理可读/可写事件
```

函数原型：

```c
int select(int nfds,
           fd_set *readfds,
           fd_set *writefds,
           fd_set *exceptfds,
           struct timeval *timeout);
```

关键点：

- `nfds` 是最大 fd 加 1。
- `select` 会修改传入的 `fd_set`。
- 每次调用前都要重新准备集合。
- 返回后通常要从 `0` 扫描到 `max_fd`。

还有几个容易漏掉的细节：

- `fd_set` 是定长位图，`FD_SET(fd, &set)` 在 fd 超过 `FD_SETSIZE` 时行为不可靠，示例代码必须显式检查。
- Linux 上 `select` 可能修改 `timeout`，跨平台代码每次调用前也应重新初始化超时时间。
- `exceptfds` 不是普通错误集合，常用于 TCP 带外数据等异常条件；普通连接错误通常也会表现为可读/可写，然后通过 `recv`、`send` 或 `getsockopt(SO_ERROR)` 发现。
- 如果需要同时等待信号和 fd，普通 `select` 可能有竞态，POSIX 提供了 `pselect` 用于原子地切换信号屏蔽字并等待。

## 本章代码

`select_echo_server.c` 是一个单线程 TCP echo server。

运行：

```bash
./build/select_echo_server 8080
```

测试：

```bash
nc 127.0.0.1 8080
```

## 代码结构

本示例维护两个核心变量：

```c
fd_set master_set;
int max_fd;
```

`master_set` 保存所有需要监听可读事件的 fd。因为 `select` 会修改传入集合，所以事件循环里每次都复制一份：

```c
fd_set read_set = master_set;
select(max_fd + 1, &read_set, NULL, NULL, NULL);
```

当 `listen_fd` 可读时，说明有新连接可以 `accept`。当客户端 fd 可读时，说明可以 `recv`。

注意“可读”的含义不只是“有业务数据”：

| 场景 | `select` 表现 | 后续处理 |
| --- | --- | --- |
| 有数据到达 | fd 可读 | `recv` 返回 `> 0` |
| 对端正常关闭 | fd 可读 | `recv` 返回 `0` |
| 连接出错 | fd 可能可读/可写 | `recv` / `send` 返回错误 |

写事件也不能长期无脑监听。大多数 TCP socket 在正常情况下经常是可写的，如果所有连接都放入 `writefds`，`select` 会不停返回，事件循环变成忙轮询。通常只有连接存在待发送数据时，才监听可写。

## 优点

- POSIX 接口，可移植性好。
- 对少量 fd 简单直观。
- 适合教学和小工具。

## 缺点

- 受 `FD_SETSIZE` 限制，常见默认值是 1024。
- 每次调用前要重新构造 `fd_set`。
- 返回后需要线性扫描。
- 大量连接时性能和可维护性都一般。

## 适合使用 select 的场景

`select` 适合：

- fd 数量很少。
- 代码需要在多种 Unix-like 系统上运行。
- 教学、调试工具、控制台程序。

它不适合 Linux 上的高并发服务核心循环。即使只考虑 `FD_SETSIZE`，很多真实服务的 fd 值也可能超过 1024，因为进程还会打开日志、文件、管道、动态库等其他 fd。
