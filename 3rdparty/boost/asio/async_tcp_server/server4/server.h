#ifndef _SERVER_H_
#define _SERVER_H_

#include "session.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace asio = boost::asio;

class Server {
    using SessionSPtr = std::shared_ptr<Session>;

public:
    Server(asio::io_context &ioc, unsigned short port);
    void removeSession(const std::string &uuid);

private:
    void startAccept();

    void handleAccept(
        SessionSPtr session,
        const boost::system::error_code &err
    );

    asio::io_context &ioc_;
    unsigned short port_;
    asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<std::string, SessionSPtr> sessions_;
};

#endif // _SERVER_H_