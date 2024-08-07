#include "session.h"
#include "server.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <iostream>

Session::Session(asio::io_context &ioc, Server *server) :
    socket_(ioc),
    server_(server),
    send_pending_(false),
    header_processed_(false) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    uuid_ = boost::uuids::to_string(uuid);
    receive_header_node_ = std::make_shared<MessageNode>(HEAD_LENGTH);
}

Session::~Session() {
    std::cerr << "~Session()" << std::endl;
}

asio::ip::tcp::socket &Session::getSocket() {
    return socket_;
}

const std::string &Session::getUuid() const {
    return uuid_;
}

void Session::start() {
    socket_.async_read_some(
        asio::buffer(data_, MAX_MESSAGE_LEN),
        std::bind(
            &Session::handleRead,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            shared_from_this() // 只是为了增加引用计数，防止在读回调时 this 对象已销毁
        )
    );
}

void Session::send(const std::string &buf) {
    std::lock_guard<std::mutex> lock(send_lock_);
    if (send_que_.size() > 0) {
        send_pending_ = true;
    }
    send_que_.push(std::make_shared<MessageNode>(buf.c_str(), buf.length()));
    if (send_pending_) {
        return;
    }
    socket_.async_write_some(
        asio::buffer(buf),
        std::bind(
            &Session::handleWrite,
            this,
            std::placeholders::_1,
            shared_from_this()
        )
    );
}

void Session::handleRead(
    const boost::system::error_code &err,
    std::size_t bytes_transferred,  // 读到的数据长度，也就是需要解包的数据长度
    std::shared_ptr<Session> self
) {
    std::cout << "[handleRead] session use_count: " << self.use_count() << std::endl;

    // 读异常
    // 客户端关闭，服务器会收到一个读事件
    if (err) {
        std::cerr << "[error] [handleRead] client closed" << std::endl;
        std::cerr << "[error] [handleRead] error msg: " << err.message() << std::endl;
        std::cerr << "[error] [handleRead] session use_count: " << self.use_count() << std::endl;
        // session 引用计数 - 1
        server_->removeSession(uuid_);
        std::cerr << "[error] [handleRead] session use_count: " << self.use_count() << std::endl;
        return;
    }

    int processed_len = 0;

    // 已处理的字节数大于 0，需要对数据进行解包
    // while 循环，一次性处理完已接收数据
    while (bytes_transferred > 0) {

        // 需要解析头部
        if (!header_processed_) {

            // 上一次处理的长度 + 当前处理的长度 < 头部规定长度
            // 受到的数据不足头部大小
            // 将已收到的数据放到头部接受缓冲区
            // 更新接收头部的节点的已处理长度
            // 清理 data_
            // 然后继续去异步读
            if (receive_header_node_->processed_len_ + bytes_transferred < HEAD_LENGTH) {
                memcpy(
                    receive_header_node_->data_ + receive_header_node_->processed_len_,
                    data_ + processed_len,
                    bytes_transferred
                );
                receive_header_node_->processed_len_ += bytes_transferred;
                memset(data_, 0, MAX_LENGTH);
                socket_.async_read_some(
                    asio::buffer(data_, MAX_LENGTH),
                    std::bind(
                        &Session::handleRead,
                        this,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        shared_from_this()
                    )
                );
                return;
            }

            // 收到的数据长度 > 头部规定长度
            // 1. 处理头部数据，`receive_header_node_` 接收
            // 2. 处理消息数据，`receive_messsage_node_` 接收

            // 1. 处理头部数据
            // 头部剩余长度 = 头部总长度 - 已处理的头部长度
            int remain_header_len = HEAD_LENGTH - receive_header_node_->processed_len_;
            // 将接收到的消息 `data_` 偏移已处理的长度 `processed_len` 后
            // 的前 `remain_header_len` 长度的数据
            // 拷贝到 `receive_header_node_` 偏移已处理的长度 `receive_header_node_->processed_len`
            memcpy(
                receive_header_node_->data_ + receive_header_node_->processed_len_,
                data_ + processed_len,
                remain_header_len
            );
            // 更新已处理的 data_ 长度 processed
            processed_len += remain_header_len;
            // 更新需要解包的数据长度
            bytes_transferred -= remain_header_len;
            // 校验头部数据，也就是这个包的信息长度
            short message_len = 0;
            memcpy(&message_len, receive_header_node_->data_, HEAD_LENGTH);
            std::cout << "message len " << message_len << std::endl;
            // 网络字节序转为本地字节序
            // message_len = asio::detail::socket_ops::network_to_host_short(message_len);
            // 长度非法
            if (message_len > MAX_LENGTH) {
                std::cerr << "invalid data length " << message_len << std::endl;
                server_->removeSession(uuid_);
                return;
            }

            // 2. 处理消息数据
            receive_message_node_ = std::make_shared<MessageNode>(message_len);
            // bytes_transferred 就是剩余的信息长度（已更新）

            // 已读的消息长度不满足消息数据的长度
            // 数据未接收全，拷贝数据到接收节点
            // 更新 receive_message_node_ 的已接收长度
            // 清理 data_
            // 更新 header_processed_ 为 true，让下一次读先处理为读完的消息数据
            // 继续异步读，以接收剩余数据
            if (bytes_transferred < message_len) {
                memcpy(
                    receive_message_node_->data_ + receive_message_node_->processed_len_,
                    data_ + processed_len,
                    bytes_transferred
                );
                receive_message_node_->processed_len_ += bytes_transferred;
                memset(data_, 0, MAX_LENGTH);
                socket_.async_read_some(
                    asio::buffer(data_, MAX_LENGTH),
                    std::bind(
                        &Session::handleRead,
                        this,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        shared_from_this()
                    )
                );
                header_processed_ = true;
                return;
            }

            // 数据接收全，可能 > message_len
            // 将数据拷贝到消息节点
            // 更新消息节点已接收的长度
            // 更新需要解包的字节长度
            // 发送接收的字节
            // 清理头部接收
            // 当需要解包的长度不为 0 时，表明接收到的数据长度大于规定的长度
            memcpy(
                receive_message_node_->data_ + receive_message_node_->processed_len_,
                data_ + processed_len,
                message_len
            );
            receive_message_node_->processed_len_ += message_len;
            processed_len += message_len;
            // 更新需要解包的字节长度
            bytes_transferred -= message_len;
            // 字符串加上结尾
            receive_message_node_->data_[receive_message_node_->total_len_] = '\0';
            std::cout << "receive data: " << receive_message_node_->data_ << std::endl;

            send(std::string(receive_message_node_->data_));

            if (bytes_transferred <= 0) {
                memset(data_, 0, MAX_LENGTH);
                socket_.async_read_some(
                    asio::buffer(data_, MAX_LENGTH),
                    std::bind(
                        &Session::handleRead,
                        this,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        shared_from_this()
                    )
                );
                return;
            }
            // 还有需要解包的数据，这些数据为下一次接收的头部
            // 更新处理头部数据的状态
            receive_header_node_->clear();
            header_processed_ = false;
            continue;
        }

        // 已处理完头部数据，处理上一次未接完的数据
        // 还需要处理的消息长度 = 消息总长度 - 上一次处理的长度
        int remain_message_len = receive_message_node_->total_len_ - receive_message_node_->processed_len_;
        // 已读字节数 < 剩余字节数
        // 还需要继续去读
        if (bytes_transferred < remain_message_len) {
            memcpy(
                receive_message_node_->data_ + receive_message_node_->processed_len_,
                data_ + processed_len,
                bytes_transferred
            );
            // 更新已处理长度
            receive_message_node_->processed_len_ += bytes_transferred;
            socket_.async_read_some(
                asio::buffer(data_, MAX_LENGTH),
                std::bind(
                    &Session::handleRead,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    shared_from_this()
                )
            );
            return;
        }

        // 已读字节数 >= 剩余字节数
        memcpy(
            receive_message_node_->data_ + receive_header_node_->processed_len_,
            data_ + processed_len,
            remain_message_len
        );
        // 更新接收缓冲区已处理长度
        receive_message_node_->processed_len_ += remain_message_len;
        // 更新剩余需要解包的长度
        bytes_transferred -= remain_message_len;
        // 更新数据缓冲区处理长度
        processed_len -= remain_message_len;

        receive_message_node_->data_[receive_message_node_->total_len_] = '\0';
        std::cout << "receive data: " << receive_message_node_->data_ << std::endl;

        std::string send_data(receive_message_node_->data_);
        std::cout << "send data: " << send_data << std::endl;

        // 将接收到的数据发送给对端
        send(send_data);
        // 清理接收缓冲区
        receive_message_node_->clear();

        // 没有需要解包的数据
        // 继续异步去读
        if (bytes_transferred <= 0) {
            memset(data_, 0, MAX_LENGTH);
            socket_.async_read_some(
                asio::buffer(data_, MAX_LENGTH),
                std::bind(
                    &Session::handleRead,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    shared_from_this()
                )
            );
            return;
        }

        // 还有需要解包的数据
        // 更新处理头部数据的状态，下次一次处理头部数据
        header_processed_ = false;
        continue;
    }

    std::cout << "[handleRead] session use_count: " << self.use_count() << std::endl;
}

void Session::handleWrite(
    const boost::system::error_code &err,
    std::shared_ptr<Session> self
) {
    std::cout << "[handleWrite] session use_count: " << self.use_count() << std::endl;

    if (err.value() != 0) {
        std::cerr << "[error] [handleWrite] error msg: " << err.message() << std::endl;
        std::cout << "[error] [handleWrite] session use_count: " << self.use_count() << std::endl;
        // 这里并没有销毁 session
        // 而是等到 handleWrite 处理完成后
        server_->removeSession(uuid_);
        std::cerr << "[error] [handleWrite] session use_count: " << self.use_count() << std::endl;
        return;
    }

    // 
    std::lock_guard<std::mutex> lock(send_lock_);
    send_que_.pop();
    if (!send_que_.empty()) {
        auto &front_node = send_que_.front();
        socket_.async_write_some(
            asio::buffer(front_node->data_, front_node->total_len_),
            std::bind(
                &Session::handleWrite,
                this,
                std::placeholders::_1,
                shared_from_this()
            )
        );
    }

    std::cout << "[handleWrite] session use_count: " << self.use_count() << std::endl;
}