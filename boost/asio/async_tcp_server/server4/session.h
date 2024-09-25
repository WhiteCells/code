#ifndef _SESSION_H_
#define _SESSION_H_

#include <boost/asio.hpp>
#include <memory>
#include <queue>
#include "message_node.h"

#define MAX_SEND_QUE 100
#define MAX_RECE_QUE 10000
#define MAX_LENGTH 1024 * 2

class Server;

namespace asio = boost::asio;

class Session :
    public std::enable_shared_from_this<Session> {

public:
    Session(asio::io_context &ioc, Server *server);
    ~Session();

    asio::ip::tcp::socket &getSocket();
    const std::string &getUuid() const;

    void start();
    void send(const std::string &buf);

private:
    void handleRead(
        const boost::system::error_code &err,
        std::size_t bytes_transferred,
        std::shared_ptr<Session> session
    );

    void handleWrite(
        const boost::system::error_code &err,
        std::shared_ptr<Session> session
    );

    asio::ip::tcp::socket socket_;
    std::string uuid_;
    Server *server_;
    char data_[MAX_LENGTH];

    /**
     * +------------------------+-------------------------+
     * |  receive_header_node_  |  receive_message_node_  |
     * +------------------------+-------------------------+
     */
    std::shared_ptr<MessageNode> receive_header_node_;
    std::shared_ptr<MessageNode> receive_message_node_;
    bool header_processed_;

    // 确保上一次发送数据完成
    // Session::send() 和 asio 回调可能不在一个线程
    // 逻辑线程和网络线程可能不在同一个线程
    std::mutex send_lock_;
    std::queue<std::shared_ptr<MessageNode>> send_que_;
    bool send_pending_;
};

#endif // _SESSION_H_