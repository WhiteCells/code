#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/asio.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace asio = boost::asio;

class Session;

class Server {
    using SessionSPtr = std::shared_ptr<Session>;
public:
    Server(asio::io_context &ioc, unsigned short port);
    ~Server();
    void startAccept();
    void removeSession(std::string uuid);

private:
    void handleAccept(
        boost::system::error_code err_code,
        std::shared_ptr<Session> session
    );

    asio::io_context &ioc_;
    asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<std::string, SessionSPtr> sessions_;
};

#endif // _SERVER_H_