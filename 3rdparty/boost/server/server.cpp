#include "server.h"
#include <iostream>

Server::Server(asio::io_context &ioc, unsigned port) :
    ioc_(ioc),
    acceptor_(ioc_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {

    startAccept();
}

Server::~Server() {

}

void Server::startAccept() {
    std::shared_ptr<Session> session = std::make_shared<Session>(ioc_, this);
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
    std::shared_ptr<Session> session,
    const boost::system::error_code &err
) {
    if (err) {
        std::cerr << "err what: " << err.what() << std::endl;
        return;
    }

    std::cout << session->getSocket().remote_endpoint().address().to_string() << std::endl;
    startAccept();
}