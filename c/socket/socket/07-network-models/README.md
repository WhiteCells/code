# 07. 常见网络模型

前面章节讲的是 socket API、阻塞/非阻塞 I/O、`select`、`poll`、`epoll`。这些是底层工具。服务端真正落地时，还要回答一个更大的问题：

> 连接来了以后，谁 accept？谁等事件？谁读写？谁解析协议？谁跑业务？谁负责把响应写回去？

这就是网络模型。

先澄清一个小误会：这里说的是 **Reactor**，不是前端框架 React。Reactor 是服务端网络编程中的事件分发模型。

---

## 1. 不止 Reactor：模型到底分几类

网络服务端模型可以从四个维度看：

| 维度 | 关注点 | 常见选择 |
| --- | --- | --- |
| I/O 方式 | `read/write` 会不会阻塞 | 阻塞、非阻塞、异步完成 |
| 等待方式 | 如何等待多个 fd | 阻塞等待、`select`、`poll`、`epoll`、`kqueue` |
| 并发载体 | 谁来并发执行 | 多进程、多线程、线程池、协程、事件循环 |
| 调度模型 | I/O 和业务如何分工 | Reactor、Proactor、Actor、Pipeline |

所以“用了 epoll”不自动等于“用了 Reactor”。`epoll` 是事件通知机制；Reactor 是围绕事件通知组织程序结构的模型。

一次请求通常经过：

```text
accept connection
  |
read bytes from socket
  |
parse protocol
  |
run business logic
  |
encode response
  |
write bytes to socket
```

不同模型的区别，就是这些步骤由哪些进程/线程/事件循环完成。

---

## 2. 阻塞串行模型

这是最基础的模型：

```text
socket -> bind -> listen

for (;;) {
    conn_fd = accept(listen_fd)
    while (recv(conn_fd)) {
        handle request
        send response
    }
    close(conn_fd)
}
```

特点：

- 一个线程。
- 阻塞 `accept`。
- 阻塞 `recv/send`。
- 同一时间主要服务一个连接。

优点：

- 极其简单。
- 非常适合学习 TCP server 基本流程。

缺点：

- 一个慢客户端会拖住整个服务。
- 无法同时处理多个活跃连接。
- `send` 也会阻塞，不只是 `recv`。

适用：

- 教学代码。
- 一次性小工具。
- 明确只有一个客户端的程序。

---

## 3. 多进程模型

多进程模型是传统 Unix 服务常见设计。

### 3.1 fork-per-connection

结构：

```text
parent:
    listen
    for (;;) {
        conn_fd = accept()
        fork()
    }

child:
    close(listen_fd)
    blocking recv/send
    close(conn_fd)
    exit
```

优点：

- 每个连接隔离在不同进程中。
- 子进程崩溃通常不影响父进程。
- 代码逻辑仍然接近阻塞同步。

缺点：

- 每个连接 fork 成本高。
- 进程数量多时调度成本大。
- 共享状态困难。

### 3.2 prefork

为了避免每个连接都 fork，可以提前 fork 一组 worker：

```text
master:
    create listen_fd
    fork N workers

worker:
    accept
    blocking or event-driven handle
```

优点：

- 进程数固定。
- 能利用多核。
- worker 崩溃后 master 可以重新拉起。

缺点：

- 多个 worker 共同 `accept` 会有负载均衡和惊群问题。
- 进程间共享连接状态麻烦。
- 适合短连接或 worker 内部继续使用事件驱动。

Nginx 的多 worker 结构有 prefork 的味道，但每个 worker 内部是事件循环，不是一个连接阻塞到底。

---

## 4. 一连接一线程模型

结构：

```text
main thread:
    conn_fd = accept()
    pthread_create(handle_client, conn_fd)

client thread:
    blocking recv/send
    close(conn_fd)
```

本章示例：

```bash
./build/thread_per_connection_echo_server 8080
```

优点：

- 代码像普通同步程序，容易理解。
- 一个连接阻塞不会卡住其他连接。
- 适合业务逻辑天然阻塞的简单服务。

缺点：

- 线程数量和连接数绑定。
- 每个线程有栈内存成本。
- 上下文切换多。
- 慢连接长期占用线程。
- 连接数达到几千、几万后很难稳定。

适用：

- 内部工具。
- 连接数较少。
- 开发效率比极限性能重要。

不适用：

- 大量长连接。
- 聊天、网关、推送、代理等连接数很高的服务。

---

## 5. 线程池模型

一连接一线程的问题是线程数量不可控。线程池把线程数固定：

```text
main thread:
    accept conn_fd
    push conn_fd to queue

worker threads:
    pop conn_fd
    blocking recv/send
    close conn_fd
```

优点：

- 控制线程数量。
- 比一连接一线程更稳定。
- 同步业务代码仍然好写。

缺点：

- 如果 worker 持有连接并阻塞读写，慢连接仍然占住 worker。
- 长连接数量远大于 worker 数时，大量连接只能排队。
- 不适合空闲连接很多、活跃连接很少的场景。

线程池模型适合：

- 短连接。
- 每个请求处理时间可控。
- 连接生命周期较短。

对于大量长连接，更常见的是：

```text
I/O 线程用 epoll 管理连接
业务任务丢给 worker 线程池
```

这就是 Reactor + 线程池。

---

## 6. Reactor 模型详解

Reactor 的核心思想：

> 事件循环等待 I/O 就绪事件，然后把事件分发给对应 handler。handler 不应该长时间阻塞。

它不是某个系统调用，而是一种组织代码的方式。

### 6.1 Reactor 的组成

典型 Reactor 包含：

| 组件 | 职责 |
| --- | --- |
| Event Demultiplexer | 等待多个 fd 的事件，Linux 上常用 `epoll_wait` |
| Reactor/Event Loop | 主循环，取事件并分发 |
| Handler | 处理具体事件，例如 accept/read/write |
| Connection State | 每条连接的输入缓冲、输出缓冲、解析状态、关闭状态 |

伪代码：

```c
for (;;) {
    events = epoll_wait(epfd);
    for each event {
        handler = event.data.ptr;
        handler->handle_event(event);
    }
}
```

这里 `event.data.ptr` 通常不是单纯 fd，而是指向连接对象：

```c
struct connection {
    int fd;
    char inbuf[...];
    char outbuf[...];
    parser_state parser;
    int closing;
};
```

这就是为什么前面 `epoll_buffered_echo_server.c` 使用连接结构，而不是只把 fd 塞进 epoll。

### 6.2 Reactor 处理一次读事件

以 TCP 为例：

```text
epoll_wait 返回 EPOLLIN
  |
找到 connection
  |
循环 recv 到 EAGAIN
  |
把字节追加到 input buffer
  |
尝试解析完整请求
  |
如果请求完整：
    生成任务或直接处理
  |
如果有响应：
    追加到 output buffer
    注册 EPOLLOUT
```

关键点：

- `EPOLLIN` 不等于只有业务数据，也可能是 EOF 或错误。
- TCP 是字节流，读到的数据要进输入缓冲。
- 非阻塞读通常要读到 `EAGAIN`。
- handler 不能长时间阻塞。

### 6.3 Reactor 处理一次写事件

```text
epoll_wait 返回 EPOLLOUT
  |
找到 connection
  |
从 output buffer 取待发送数据
  |
循环 send
  |
写完：移除 EPOLLOUT
  |
没写完且 EAGAIN：保留剩余数据，继续等待 EPOLLOUT
```

关键点：

- `EPOLLOUT` 不能一直开，否则 socket 大多时候可写，会导致事件循环频繁醒来。
- 一次 `send` 可能短写。
- 输出缓冲过大时要做背压：暂停读、丢弃连接或限速。

### 6.4 单线程 Reactor

结构：

```text
one thread:
    epoll_wait
    accept
    read
    parse
    business
    write
```

适合：

- 业务极轻。
- I/O 密集。
- 希望避免锁。

优点：

- 连接状态只在一个线程里，几乎不需要锁。
- 内存和调度成本低。
- 非常适合大量空闲长连接。

缺点：

- 不能做慢业务。
- CPU 重任务会卡住所有连接。
- 单线程无法吃满多核。

典型原则：

```text
I/O 线程只做快事情：
accept、recv、parse 少量数据、append buffer、send

慢事情交出去：
数据库、磁盘、RPC、压缩、复杂计算
```

### 6.5 Reactor + 线程池

结构：

```text
Reactor thread:
    epoll_wait
    read request
    parse
    push business task to worker queue

Worker threads:
    pop task
    run business
    produce response
    push response to done queue
    notify reactor

Reactor thread:
    append response to output buffer
    enable EPOLLOUT
```

这比普通线程池多了一个重要原则：

> socket fd 和连接状态最好由 Reactor 线程拥有，worker 不直接读写 socket。

原因：

- 避免多个线程同时 `send/recv` 同一个 fd。
- 避免连接关闭与 worker 写回响应竞态。
- 输出缓冲、协议状态更容易维护。

跨线程通知常见方式：

| 方式 | 说明 |
| --- | --- |
| `eventfd` | Linux 常用，适合唤醒 epoll |
| pipe | 可移植性较好，也能放进 select/poll/epoll |
| condition variable | 适合线程间等待，但不能直接唤醒 epoll fd 集合 |
| lock-free queue | 降低锁开销，但实现复杂 |

本章的 `reactor_threadpool_demo.c` 使用：

```text
worker push done_queue
worker write eventfd
reactor epoll_wait 被唤醒
reactor drain eventfd
reactor send response
```

### 6.6 多 Reactor

单个 Reactor 线程仍可能成为瓶颈。多 Reactor 把连接分给多个 I/O 线程：

```text
main reactor:
    accept
    choose sub reactor
    hand off conn_fd

sub reactor 0:
    epoll_wait/read/write connections assigned to it

sub reactor 1:
    epoll_wait/read/write connections assigned to it
```

核心原则：

> 一条连接固定归属于一个 sub reactor，连接状态只在该 sub reactor 线程修改。

新连接分发方式：

| 方式 | 说明 |
| --- | --- |
| main reactor accept 后分发 | main 线程统一 accept，round-robin 给 sub reactor |
| 多 worker 直接 accept | 多个 worker 共享监听 fd，或使用 `SO_REUSEPORT` |
| 负载感知分发 | 按连接数、队列长度或 CPU 负载选择 reactor |

main reactor 把 fd 交给 sub reactor 时，常见流程：

```text
main accept conn_fd
  |
set nonblocking
  |
push conn_fd to sub reactor queue
  |
write sub reactor's eventfd
  |
sub reactor wake up
  |
sub reactor epoll_ctl ADD conn_fd
```

本章的 `multi_reactor_demo.c` 就演示这个骨架。

多 Reactor 的难点：

- fd 跨线程移交要有清晰所有权。
- sub reactor 关闭连接时，要确保没有其他线程继续使用该 fd。
- worker 业务结果返回时，要投递回连接所属 reactor。
- 定时器、限流、连接统计也要按线程归属设计。

---

## 7. Proactor 模型

Reactor 等待的是“可做 I/O”：

```text
fd readable -> 应用调用 recv
fd writable -> 应用调用 send
```

Proactor 等待的是“I/O 已完成”：

```text
提交 read 请求
  |
内核/运行时完成 read
  |
应用收到完成事件和结果
```

对比：

| 模型 | 事件含义 | 应用动作 |
| --- | --- | --- |
| Reactor | fd 就绪 | 应用执行 `recv/send` |
| Proactor | I/O 完成 | 应用处理完成结果 |

典型实现：

- Windows IOCP。
- Linux `io_uring` 可以写出接近 Proactor 的模型。
- POSIX AIO 更偏文件 I/O，网络服务里使用不如 epoll 常见。

注意：

- `select/poll/epoll` 是 readiness notification。
- IOCP/io_uring completion queue 是 completion notification。

Proactor 优点：

- I/O 提交和完成解耦。
- 理论上可以减少一些系统调用和线程阻塞。
- 适合和完成队列、批量提交结合。

难点：

- 生命周期管理更复杂。
- buffer 在 I/O 完成前不能释放。
- 取消、超时、关闭连接时的竞态更难处理。

---

## 8. Actor、Pipeline 与协程模型

这些不是 socket 系统调用级别的模型，但在现代服务里很常见。

### Actor 模型

Actor 把状态封装在 actor 内部，通过消息通信：

```text
connection actor
  receives: bytes, timeout, close, response
  owns: parser state, output buffer
```

优点：

- 状态归属清晰。
- 避免共享内存并发修改。

缺点：

- 消息队列、调度器、背压都要设计好。
- 在 C 里手写 Actor 运行时成本较高。

### Pipeline 模型

把请求处理拆成多个阶段：

```text
read -> decode -> auth -> business -> encode -> write
```

每个阶段可以是函数、线程池、队列或协程。适合复杂协议和网关。

难点是：每个阶段处理速度不同，队列可能积压，需要背压。

### 协程模型

协程让代码写起来像同步阻塞：

```text
data = co_await socket.read()
response = handle(data)
co_await socket.write(response)
```

底层仍然可能是：

```text
nonblocking fd + epoll/io_uring + scheduler
```

优点：

- 代码可读性好。
- 每个连接像独立执行流。
- 比线程更轻。

缺点：

- 调度器复杂。
- 阻塞系统调用会卡住线程，必须配合异步封装。
- C 语言原生没有高级协程支持，通常依赖库或切换到 C++/Go/Rust 等语言生态。

Go 的 goroutine 网络模型，本质上就是运行时替你封装了非阻塞 I/O、多路复用和调度器。

---

## 9. 连接状态机

事件驱动模型里，连接不是“函数调用栈上的局部变量”，而是长期存在的状态对象。

常见状态：

```text
ACCEPTED
  |
READING
  |
PARSING
  |
PROCESSING
  |
WRITING
  |
IDLE / CLOSING / CLOSED
```

典型连接结构：

```c
struct connection {
    int fd;
    char inbuf[IN_CAP];
    size_t in_len;
    char outbuf[OUT_CAP];
    size_t out_sent;
    size_t out_len;
    int processing;
    int closing;
};
```

必须回答的问题：

- 半包来了，`inbuf` 怎么保存？
- 多个请求粘在一起，如何循环解析？
- 响应没写完，剩余数据放在哪里？
- worker 正在处理时，客户端断开怎么办？
- 关闭连接前，输出缓冲是否要尽量 flush？
- 输出缓冲爆了，是暂停读还是断开连接？
- 空闲连接多久超时？

这就是 Reactor 文档里最容易被讲浅的地方：真正复杂的是连接状态，不是 `epoll_wait` 那行代码。

---

## 10. 模型对比

| 模型 | 并发能力 | 代码复杂度 | 多核利用 | 适合 |
| --- | --- | --- | --- | --- |
| 阻塞串行 | 很低 | 很低 | 差 | 教学、小工具 |
| fork-per-connection | 低到中 | 低 | 一般 | 传统短连接服务 |
| prefork | 中 | 中 | 好 | 多进程服务、隔离要求高 |
| 一连接一线程 | 中 | 低 | 好 | 连接少、业务阻塞 |
| 线程池 | 中 | 中 | 好 | 短连接、中等并发 |
| 单 Reactor | 高 | 中 | 差 | I/O 密集、业务很轻 |
| Reactor + 线程池 | 高 | 高 | 好 | I/O 高并发 + 业务任务 |
| 多 Reactor | 很高 | 很高 | 很好 | 高并发长连接 |
| Proactor | 高 | 高 | 好 | IOCP/io_uring 场景 |
| 协程 | 高 | 中到高 | 好 | 语言运行时支持较好时 |

---

## 11. 本章示例

| 文件 | 模型 | 说明 |
| --- | --- | --- |
| `thread_per_connection_echo_server.c` | 一连接一线程 | 每个连接一个 pthread，阻塞 `recv/send` |
| `reactor_threadpool_demo.c` | Reactor + 线程池 | Reactor 管 I/O，worker 处理任务，`eventfd` 唤醒 |
| `multi_reactor_demo.c` | main Reactor + sub Reactors | main 接收连接，round-robin 分发给多个 sub reactor |

编译：

```bash
make
```

运行一连接一线程：

```bash
./build/thread_per_connection_echo_server 8080
```

运行 Reactor + 线程池：

```bash
./build/reactor_threadpool_demo 8080
```

运行 multi-Reactor：

```bash
./build/multi_reactor_demo 8080
```

测试：

```bash
nc 127.0.0.1 8080
```

这些示例仍然是教学骨架，不是生产服务器。真实服务还需要完整协议解析、输出缓冲、超时、限流、日志、优雅关闭、内存池和更严格的错误处理。
