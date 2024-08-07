#include "server.h"
#include <iostream>

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