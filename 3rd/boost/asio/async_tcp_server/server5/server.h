#ifndef _SERVER_H_
#define _SERVER_H_

#include "session.h"
#include <unordered_map>

/**
 * Server accepts new connections
 * Session management by Server
 */
class Server
{
public:
    Server(asio::io_context &ioc, unsigned short port);
    ~Server();

    // receive new connection
    // and also callback after receiving new connection
    void startAccept();

    // Session use_count - 1
    void removeSession(const std::string &uid);

private:
    // callback after receiving a new connection
    void handleAccept(
        const boost::system::error_code &err_code,
        std::shared_ptr<Session> session);

    asio::io_context &ioc_;
    asio::ip::tcp::acceptor acceptor_;
    // manage Session and extend their lifecycle
    std::unordered_map<std::string, std::shared_ptr<Session>> sessions_;
};

#endif // _SERVER_H_