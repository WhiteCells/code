#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace asio = boost::asio;

class Session :
    public std::enable_shared_from_this<Session> {

public:
    Session(asio::io_context &ioc);
    ~Session();
    asio::ip::tcp::socket &getSocket();
    void start();

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

    enum { MAX_MESSAGE_LEN = 1024 };
    char data_[MAX_MESSAGE_LEN];
    asio::ip::tcp::socket socket_;
};

class Server {
    using SessionSPtr = std::shared_ptr<Session>;
    
public:
    Server(asio::io_context &ioc, unsigned short port);

private:
    void startAccept();

    void handleAccept(
        SessionSPtr session,
        const boost::system::error_code &err
    );
    asio::io_context &ioc_;
    unsigned short port_;
    asio::ip::tcp::acceptor acceptor_;
};