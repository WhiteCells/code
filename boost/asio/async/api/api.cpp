#include <boost/asio.hpp>
#include <memory>
#include <queue>
#include <iostream>

#define MAX_MESSAGE_LEN 1024

namespace asio = boost::asio;

class MessageNode {
    friend class Session;
public:
    MessageNode(int total_len) :
        total_len_(total_len),
        processed_len_(0) {
        message_ = new char[total_len_];
    }
    MessageNode(const char *message, int total_len) :
        total_len_(total_len),
        processed_len_(0) {
        message_ = new char[total_len_];
        memcpy(message_, message, strlen(message));
    }
    ~MessageNode() {
        if (message_) {
            delete[] message_;
            message_ = nullptr;
        }
    }

private:
    char *message_;

    /**
     *   +-----+--------------+
     *   |     |              |
     *   +-----+--------------+
     *         |              |
     *    processed_len_  total_len_
     */
    const int total_len_;
    int processed_len_;
};

// 当有客户端连接时，由 Sesssion 管理
class Session {
    using SocketSPtr = std::shared_ptr<asio::ip::tcp::socket>;
    using MessageNodeSPtr = std::shared_ptr<MessageNode>;

public:
    Session(SocketSPtr socket) :
        socket_(socket),
        send_pending_(false),
        receive_pending_(false) {

    }

    void connect(const asio::ip::tcp::endpoint &endpoint) {
        socket_->connect(endpoint);
    }

    /////////////////////////////////////
    /////////////////////////////////////
    /////////////////////////////////////
    // 异步写

    void write1(const std::string &buf) {
        send_queue_.emplace(std::make_shared<MessageNode>(
            buf.c_str(), buf.length()
        ));
        if (send_pending_) {
            // 存在未发送完的数据
            // 让回调函数继续执行
            return;
        }
        socket_->async_write_some(
            asio::buffer(buf),
            std::bind(
                &Session::writeCallBack1,
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );
        // 异步发送数据，数据可能会未发送完
        // 当发送完后，在异步写的回调中更新 `send_pending_`
        send_pending_ = true;
    }

    void writeCallBack1(
        boost::system::error_code &err,
        std::size_t bytes_transferred // 已传输字节
    ) {
        if (err.value() != 0) {
            return;
        }

        MessageNodeSPtr &front = send_queue_.front();

        front->processed_len_ += bytes_transferred;
        if (front->processed_len_ < front->total_len_) {
            socket_->async_write_some(
                asio::buffer(
                    front->message_ + front->processed_len_,  // 剩余数据的首地址：数据首地址偏移已处理长度
                    front->total_len_ - front->processed_len_ // 剩余数据的长度  ：数据总长度减去已处理长度
                ),
                std::bind(
                    &Session::writeCallBack1,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2
                )
            );
            return;
        }

        // 已处理完队列头部
        send_queue_.pop();

        if (send_queue_.empty()) {
            // 数据都发送完成
            send_pending_ = false;
            return;
        } else {
            // 数据未发送完成
            MessageNodeSPtr &front = send_queue_.front();
            socket_->async_write_some(
                asio::buffer(
                    front->message_,  // 第一次写时 `processed_len == 0`
                    front->total_len_
                ),
                std::bind(
                    &Session::writeCallBack1,
                    std::placeholders::_1,
                    std::placeholders::_2
                )
            );
        }
    }

    // 常用
    // 减少回调的调用
    void write2(const std::string &buf) {
        send_queue_.emplace(std::make_shared<MessageNode>(
            buf.c_str(), buf.length())
        );
        if (send_pending_) {
            return;
        }
        // 底层调用 `async_write_some()` 
        socket_->async_send(
            asio::buffer(buf),
            std::bind(
                &Session::writeCallBack2,
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );

        send_pending_ = true;
    }

    void writeCallBack2(
        boost::system::error_code &err,
        std::size_t bytes_transferred
    ) {
        if (err.value() != 0) {
            std::cerr << "[error message]: " << err.message() << std::endl;
            return;
        }

        send_queue_.pop();
        if (send_queue_.empty()) {
            send_pending_ = false;
            return;
        }

        auto &front_data = send_queue_.front();
        socket_->async_send(
            asio::buffer(
                front_data->message_,
                front_data->total_len_
            ),
            std::bind(
                &Session::writeCallBack2,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );
    }

    // 多线程调用异步写，可能会导致数据乱序
    // 需要使用队列保证发送数据的顺序性
    void write3(const std::string &buf) {
        send_node_ = std::make_shared<MessageNode>(buf.c_str(), buf.length());
        socket_->async_write_some(
            asio::buffer(
                send_node_->message_,
                send_node_->total_len_
            ),
            std::bind(
                &Session::writeCallBack3,
                this,
                std::placeholders::_1,
                std::placeholders::_2,
                send_node_ // 增加引用计数
            )
        );
    }

    void writeCallBack3(
        const boost::system::error_code &err,
        std::size_t bytes_transferred,
        MessageNodeSPtr node
    ) {
        if (err.value() != 0) {
            return;
        }
        if (bytes_transferred + node->processed_len_ < node->total_len_) {
            node->processed_len_ += bytes_transferred;
            socket_->async_write_some(
                asio::buffer(
                    node->message_ + node->processed_len_,
                    node->total_len_ - node->processed_len_
                ),
                std::bind(
                    &Session::writeCallBack3,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    node
                )
            );
        }
    }

    /////////////////////////////////////
    /////////////////////////////////////
    /////////////////////////////////////
    // 异步读

    // 常用
    void read1() {
        if (receive_pending_) {
            return;
        }
        receive_node_ = std::make_shared<MessageNode>(
            MAX_MESSAGE_LEN
        );
        socket_->async_read_some(
            asio::buffer(
                receive_node_->message_,
                receive_node_->total_len_
            ),
            std::bind(
                &Session::readCallBack1,
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );
        receive_pending_ = true;
    }

    void readCallBack1(
        boost::system::error_code &err,
        std::size_t bytes_transferred
    ) {
        if (err.value() != 0) {
            std::cerr << "[error message: ]" << err.message() << std::endl;
            return;
        }

        receive_node_->processed_len_ += bytes_transferred;
        if (receive_node_->processed_len_ < receive_node_->total_len_) {
            socket_->async_read_some(
                asio::buffer(
                    receive_node_->message_ + receive_node_->processed_len_,
                    receive_node_->total_len_ - receive_node_->processed_len_
                ),
                std::bind(
                    &Session::readCallBack1,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2
                )
            );
        } else {
            receive_pending_ = false;
        }
    }

    // 减少回调的调用
    void read2() {
        if (receive_pending_) {
            return;
        }
        receive_node_ = std::make_shared<MessageNode>(
            MAX_MESSAGE_LEN
        );
        // 底层调用 `async_read_some`
        socket_->async_receive(
            asio::buffer(
                receive_node_->message_,
                receive_node_->total_len_
            ),
            std::bind(
                &Session::readCallBack2,
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );
        receive_pending_ = true;
    }

    void readCallBack2(
        boost::system::error_code &err,
        std::size_t bytes_transferred
    ) {
        if (err.value() != 0) {
            std::cerr << "[error message]: " << err.message() << std::endl;
            return;
        }

        // receive_pending_ = false;
        receive_node_->processed_len_ += bytes_transferred;
        if (receive_node_->processed_len_ == receive_node_->total_len_) {
            receive_pending_ = false;
        }
    }

private:
    SocketSPtr socket_;
    MessageNodeSPtr send_node_;
    MessageNodeSPtr receive_node_;
    std::queue<MessageNodeSPtr> send_queue_;
    bool send_pending_;
    bool receive_pending_;
};