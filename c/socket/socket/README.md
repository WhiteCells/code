# Linux/Unix Socket 网络编程教程

这个目录是一套面向 C 语言初学网络编程读者的分模块教程。每个章节目录都包含：

- `README.md`：本章概念、流程、代码讲解和常见注意点。
- `.c` 示例代码：可以在 Linux 下用 `gcc` 编译运行。

推荐阅读顺序：

| 顺序 | 目录 | 主题 |
| --- | --- | --- |
| 1 | `01-basic-tcp-udp` | socket 基础、TCP/UDP client 和 server |
| 2 | `02-blocking-nonblocking` | 阻塞与非阻塞 I/O、`EAGAIN` / `EWOULDBLOCK` |
| 3 | `03-select` | `select` 的模型、优缺点和 echo server |
| 4 | `04-poll` | `poll` 的模型、优缺点和 echo server |
| 5 | `05-epoll` | `epoll`、LT/ET、连接状态机、输出缓冲 |
| 6 | `06-summary-and-pitfalls` | 三者对比、POSIX/Linux 差异、生产常见坑 |
| 7 | `07-network-models` | 阻塞、多进程、多线程、线程池、Reactor、多 Reactor、Proactor、协程 |

原来的完整长文保留在仓库根目录的 `socket.md`，适合一次性通读。这个子目录更适合边读边编译运行。

## 编译全部示例

在 `socket` 目录下运行：

```bash
make
```

生成的可执行文件会放在 `build/` 目录。

清理：

```bash
make clean
```

## 快速运行

启动一个 TCP echo server：

```bash
./build/epoll_echo_server 8080
```

另开一个终端测试：

```bash
nc 127.0.0.1 8080
```

输入任意文本，服务器会原样返回。

## 文件结构

```text
socket/
├── README.md
├── Makefile
├── common/
│   ├── net_utils.c
│   ├── net_utils.h
│   └── README.md
├── 01-basic-tcp-udp/
├── 02-blocking-nonblocking/
├── 03-select/
├── 04-poll/
├── 05-epoll/
├── 06-summary-and-pitfalls/
└── 07-network-models/
```

`common/` 中的工具函数用于创建监听 socket、设置非阻塞、处理 `send_all` 等重复逻辑。这样每章代码可以更专注于自己的主题。

## 进阶示例

`05-epoll/epoll_buffered_echo_server.c` 是本教程最接近真实服务端结构的示例。它不再假设 `send` 一定能马上写完，而是为每个连接维护输出缓冲区，并按需注册 `EPOLLOUT`。如果你已经看完基础 echo server，建议重点读这个文件。

`07-network-models/` 系统讲解常见服务端网络模型，并提供一连接一线程、Reactor + 线程池、multi-Reactor 三个示例，用来对比不同模型的结构和取舍。
