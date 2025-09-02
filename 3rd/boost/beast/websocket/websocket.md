WebSocket 需要一个有状态对象，由 Beast 中的一个类模板 websocket::stream 表示该接口使用分层流模型，一个 websocket stream 对象包含另一个流对象，称为下一层，用于执行 I/O 操作

```cpp
template<typename NextLayer, bool defaultSupported = true>
class stream;
```

NextLayer: 表示 WebSocket 连接使用的下一层流类型，例如 TCP 套接字或 TLS 握手后的数据流，
defaultSupported: 表示是否支持 WebSocket 协议内置的压缩功能