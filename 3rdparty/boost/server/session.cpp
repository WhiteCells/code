#include "session.h"

Session::Session(asio::io_context &ioc, Server *server) :
    socket_(ioc) {

}

Session::~Session() {

}


asio::ip::tcp::socket &Session::getSocket() {
    return socket_;
}
