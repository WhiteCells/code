#include "server.h"

Session::Session(asio::io_context &ioc, Server *server) :
    socket_(ioc),
    server_(server) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    uuid_ = boost::uuids::to_string(uuid);
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
    memset(data_, 0, MAX_MESSAGE_LEN);
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

void Session::handleRead(
    const boost::system::error_code &err,
    std::size_t bytes_transferred,
    std::shared_ptr<Session> self
) {
    std::cout << "===> [handleRead] session use_count: " << self.use_count() << std::endl;

    if (err) {
        // 客户端关闭，服务器会收到一个读事件
        std::cerr << "[error] [handleRead] client closed" << std::endl;
        std::cerr << "[error] [handleRead] error msg: " << err.message() << std::endl;
        std::cout << "[error] [handleRead] session use_count: " << self.use_count() << std::endl;
        // 这里并没有真正移除 session
        server_->removeSession(uuid_);
        std::cerr << "[error] [handleRead] session use_count: " << self.use_count() << std::endl;
        return;
    }

    std::cout << "receive data: " << data_ << std::endl;

    // socket_.async_read_some(
    //     asio::buffer(data_, MAX_MESSAGE_LEN),
    //     std::bind(
    //         &Session::handleRead,
    //         this,
    //         std::placeholders::_1,
    //         std::placeholders::_2,
    //         shared_from_this()
    //     )
    // );

    socket_.async_write_some(
        asio::buffer(data_, bytes_transferred),
        std::bind(
            &Session::handleWrite,
            this,
            std::placeholders::_1,
            shared_from_this()
        )
    );

    std::cout << "<=== [handleRead] session use_count: " << self.use_count() << std::endl;
}

void Session::handleWrite(
    const boost::system::error_code &err,
    std::shared_ptr<Session> self
) {
    std::cout << "===> [handleWrite] session use_count: " << self.use_count() << std::endl;

    if (err.value() != 0) {
        std::cerr << "[error] [handleWrite] error msg: " << err.message() << std::endl;
        std::cout << "[error] [handleWrite] session use_count: " << self.use_count() << std::endl;
        // session 引用计数 - 1
        server_->removeSession(uuid_);
        std::cerr << "[error] [handleWrite] session use_count: " << self.use_count() << std::endl;
        return;
    }

    memset(data_, 0, MAX_MESSAGE_LEN);

    socket_.async_read_some(
        asio::buffer(data_, MAX_MESSAGE_LEN),
        std::bind(
            &Session::handleRead,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            shared_from_this()
        )
    );

    std::cout << "<=== [handleWrite] session use_count: " << self.use_count() << std::endl;
}

Server::Server(
    asio::io_context &ioc,
    unsigned short port
) :
    ioc_(ioc),
    port_(port),
    acceptor_(ioc_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port_)) {
    std::cout << "server start listen " << port_ << std::endl;
    startAccept();
}

void Server::removeSession(const std::string &uuid) {
    sessions_.erase(uuid);
}

void Server::startAccept() {
    SessionSPtr session = std::make_shared<Session>(ioc_, this);
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

void Server::handleAccept(
    SessionSPtr session,
    const boost::system::error_code &err
) {
    if (err.value() != 0) {
        std::cerr << err.message() << std::endl;
        return;
    }
    std::cout << "client ip: "
        << session->getSocket().remote_endpoint().address().to_string()
        << std::endl;

    sessions_[session->getUuid()] = session;
    session->start();

    startAccept();
}

int main(int argc, char *argv[]) {
    try {
        asio::io_context ioc;
        Server server(ioc, 11451);
        ioc.run();
    } catch (std::exception &exp) {
        std::cerr << "[exception]: " << exp.what() << std::endl;
    }
    return 0;
}