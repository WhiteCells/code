#ifndef _SESSION_H_
#define _SESSION_H_

#include <boost/asio.hpp>

namespace asio = boost::asio;

class Server;

class Session {
public:
    Session(asio::io_context &ioc, Server *server);
    ~Session();

    asio::ip::tcp::socket &getSocket();

private:
    asio::ip::tcp::socket socket_;
};

#endif // _SESSION_H_