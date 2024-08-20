#include "server.h"
#include "session.h"
#include "io_context_pool.h"

Server::Server(asio::io_context &ioc, unsigned short port) :
    ioc_(ioc),
    acceptor_(ioc, {asio::ip::tcp::v4(), port}) {

}

Server::~Server() {

}

void Server::startAccept() {
    asio::io_context &ioc = IOContextPool::getInstance()->getIoContext();
    std::shared_ptr<Session> session = std::make_shared<Session>(ioc, this);
    acceptor_.async_accept(
        session->getClientSocket(),
        std::bind(
            &Server::handleAccept,
            this,
            std::placeholders::_1,
            session
        )
    );
}

void Server::removeSession(std::string uuid) {
    if (sessions_.count(uuid)) {
        sessions_.erase(uuid);
    }
}

void Server::handleAccept(
    boost::system::error_code err_code,
    std::shared_ptr<Session> session
) {
    if (err_code) {
        std::cerr << "err value: " << err_code.value() << std::endl;
        std::cerr << "err message: " << err_code.message() << std::endl;
        return;
    }

    session->startRecv();

    sessions_.insert({session->getUuid(), session});

    startAccept();
}

int main(int argc, char *argv[]) {
    try {
        asio::io_context ioc;
        Server server(ioc, 10101);
        server.startAccept();
        ioc.run();
    } catch (std::exception &exp) {
        std::cerr << "exception: " << exp.what() << std::endl;
    }
    return 0;
}