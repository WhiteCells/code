#ifndef _SERVER_H_
#define _SERVER_H_

#include "session.h"
#include <memory>

namespace asio = boost::asio;

/**
 * manager `Session`
 * acceptor new connection
 */
class Server {
public:
    Server(asio::io_context &ioc, unsigned port);
    ~Server();

private:
    /// @brief 异步的接收连接，同时也是连接完后的回调中需要执行的，用于接收新连接
    void startAccept();

    /**
     * 接收连接完成后的回调
     * session 用于增加 session 引用计数
     * err 为 asio 接收完成后返回的错误码
     */
    void handleAccept(
        std::shared_ptr<Session> session,
        const boost::system::error_code &err
    );

    asio::io_context &ioc_;
    asio::ip::tcp::acceptor acceptor_;
};

#endif // _SERVER_H_