#include <boost/asio.hpp>
#include <string>
#include <iostream>

namespace asio = boost::asio;

int main(int argc, char *argv[]) {
    asio::io_context ioc;
    asio::ip::tcp::socket socket(ioc);
    asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"), 50555);
    boost::system::error_code err_code;
    socket.connect(endpoint, err_code);
    if (err_code) {
        std::cout << "err value: " << err_code.value() << std::endl;
        std::cout << "err message: " << err_code.message() << std::endl;
        return EXIT_FAILURE;
    }
    // [id] [len] [data]
    short id = 10;
    id = htons(id);
    const char *data = "{"":{}}";
    short len = strlen(data);
    short tmp_len = len;
    len = htons(len);
    char *send_node = new char[4 + len];
    memcpy(send_node, &id, 2);
    memcpy(send_node + 2, &len, 2);
    memcpy(send_node + 4, data, tmp_len);
    asio::write(socket, asio::buffer(send_node, 4 + tmp_len));
    return 0;
}