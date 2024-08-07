#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;

class Session {

public:
    Session(asio::io_context &ioc) :
        socket_(ioc) {

    }

    ~Session() {
        std::cout << "~Session()" << std::endl;
    }

    asio::ip::tcp::socket &getSocket() {
        return socket_;
    }

    void start() {
        memset(data_, 0, MAX_MESSAGE_LEN);
        socket_.async_read_some(
            asio::buffer(data_, MAX_MESSAGE_LEN),
            std::bind(
                &Session::handleRead,
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );
    }

private:
    void handleRead(
        const boost::system::error_code &err,
        std::size_t bytes_transferred
    ) {
        if (err.value() != 0) {
            // 客户端关闭，服务器会收到一个读事件
            std::cerr << "client closed " << std::endl;
            std::cerr << "[error code]: " << err.value() << std::endl;
            std::cerr << "[error msg ]: " << err.message() << std::endl;
            delete this;
            return;
        }

        std::cout << "receive data: " << data_ << std::endl;

        socket_.async_read_some(
            asio::buffer(data_, MAX_MESSAGE_LEN),
            std::bind(
                &Session::handleRead,
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );

        asio::async_write(
            socket_,
            asio::buffer(data_, bytes_transferred),
            std::bind(
                &Session::handleWrite,
                this,
                std::placeholders::_1
            )
        );
    }

    void handleWrite(
        const boost::system::error_code &err
    ) {
        if (err.value() != 0) {
            // 当 socket 绑定读事件和写事件时
            // 客户端在发送数据时，客户端关闭，服务器发现客户端关闭
            // 在服务器向客户端发送数据时，会发生错误，在 `handleWrite()` 执行 `delete this`
            // 而客户端关闭时，会向服务器发送一个读事件
            // 这个读事件会发生错误，在 `handleRead()` 再次执行 `delete this`
            delete this;
            return;
        }
        socket_.async_read_some(
            asio::buffer(data_, MAX_MESSAGE_LEN),
            std::bind(
                &Session::handleRead,
                this,
                std::placeholders::_1,
                std::placeholders::_2
            )
        );
    }

    enum {
        MAX_MESSAGE_LEN = 1024,
    };
    char data_[MAX_MESSAGE_LEN];
    asio::ip::tcp::socket socket_;
};

class Server {
    
public:
    Server(
        asio::io_context &ioc,
        unsigned short port
    ) :
        ioc_(ioc),
        port_(port),
        acceptor_(ioc_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port_)) {
        std::cout << "server start listen " << port_ << std::endl;
        startAccept();
    }

private:
    void startAccept() {
        Session *session = new Session(ioc_);
        acceptor_.async_accept(
            session->getSocket(),
            std::bind(
                &Server::handleAccept,
                this,
                session,
                std::placeholders::_1
            )
        );
    }

    void handleAccept(
        Session *session,
        const boost::system::error_code &err
    ) {
        if (err.value() != 0) {
            delete session;
            session = nullptr;
            return;
        }
        std::cout << "client ip: "
            << session->getSocket().remote_endpoint().address().to_string()
            << std::endl;
        session->start();

        startAccept();
    }

    asio::io_context &ioc_;
    unsigned short port_;
    asio::ip::tcp::acceptor acceptor_;
};

int main(int argc, char *argv[]) {
    try {
        asio::io_context ioc;
        Server server(ioc, 11451);
        ioc.run();
    } catch (std::exception &exp) {
        std::cerr << "exception: " << exp.what() << std::endl;
    }
    return 0;
}