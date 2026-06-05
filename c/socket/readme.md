# Socket

这是一个 Linux/Unix socket 网络编程学习项目。

## 入口
- `socket.md`：单文件完整教程，适合一次性通读。
- `socket/`：拆分后的多目录教程，每个目录包含对应文档和 C 示例代码。

## 编译示例

```bash
cd socket
make
```

生成的可执行文件位于：

```text
socket/build/
```

例如运行 epoll echo server：

```bash
./build/epoll_echo_server 8080
```

再用 `nc` 测试：

```bash
nc 127.0.0.1 8080
```
