#include "server.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        asio::io_context ioc;
        Server server(ioc, 10000);
        ioc.run();
    } catch (boost::system::system_error &err) {
        std::cerr << "err code: " << err.code() << std::endl;
        std::cerr << "err what: " << err.what() << std::endl;
    }
    return 0;
}