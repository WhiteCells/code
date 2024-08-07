#include <boost/asio.hpp>
#include <iostream>
#include <string>

#define MAX_MESSAGE_LEN 1024

namespace asio = boost::asio;

int main(int argc, char *argv[]) {
    // std::string raw_ip_address {"127.0.0.1"};
    std::string raw_ip_address {"192.168.1.17"}; 
    unsigned short port_num = 11451;

    try {
        asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address);
        asio::ip::tcp::endpoint endpoint(ip_address, port_num);
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc);
        boost::system::error_code error;
        socket.connect(endpoint, error);
        if (error) {
            std::cerr << "[error code]: " << error.value() << std::endl;
            std::cerr << "[error msg ]: " << error.message() << std::endl;
            return EXIT_FAILURE;
        }

        for (;;) {
            std::cout << "[client] send message: ";
            char request[MAX_MESSAGE_LEN];
            std::cin.getline(request, MAX_MESSAGE_LEN);
            std::size_t request_len = strlen(request);
            if (request_len == 0) {
                continue;
            }
            asio::write(socket, asio::buffer(request, request_len), error);
            if (error) {
                std::cerr << "[error code]: " << error.value() << std::endl;
                std::cerr << "[error     ]: " << error.message() << std::endl;
                // continue;
                return EXIT_FAILURE;
            }

            char response[MAX_MESSAGE_LEN];
            std::size_t response_len = asio::read(
                socket, asio::buffer(response, request_len)
            );

            if (response_len < 0) {
                std::cerr << "system error" << std::endl;
                return EXIT_FAILURE;
            } else if (response_len == 0) {
                std::cerr << "endpoint shutdown" << std::endl;
                return EXIT_FAILURE;
            }
            std::cout << "[client] receive message: ";
            std::cout.write(response, response_len) << std::endl;
            // return EXIT_SUCCESS;
        }

    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}