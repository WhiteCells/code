#include <iostream>
#include <boost/asio.hpp>
#include <thread>

namespace asio = boost::asio;

const int MAX_LENGTH = 1024 * 2;
const int HEAD_LENGTH = 2;

int main(int argc, char *argv[]) {
    try {
        asio::io_context ioc;
        asio::ip::tcp::endpoint endpoint(
            asio::ip::address::from_string("127.0.0.1"),
            // 11451
            // 10086
            10101
        );
        asio::ip::tcp::socket socket(ioc);
        boost::system::error_code err;
        socket.connect(endpoint, err);
        if (err) {
            std::cerr << "connection failed " << err.value() << std::endl;
            std::cerr << "error message " << err.message() << std::endl;
            // std::cerr << "error what " << err.what() << std::endl;
            return 0;
        }

        std::thread send_thread([&socket]() {
            for (;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "send message ..." << std::endl;

                const char *request {"request message"};
                short request_len = strlen(request);
                request_len = asio::detail::socket_ops::host_to_network_short(request_len);

                char send_data[MAX_LENGTH] {};
                memcpy(send_data, &request_len, HEAD_LENGTH);
                memcpy(send_data + HEAD_LENGTH, request, request_len);

                asio::write(
                    socket,
                    asio::buffer(send_data, HEAD_LENGTH + request_len)
                );
            }
        });

        std::thread rece_thraed([&socket]() {
            for (;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cerr << "receive message ..." << std::endl;
                char response_head[HEAD_LENGTH];
                asio::read(
                    socket,
                    asio::buffer(response_head, HEAD_LENGTH)
                );
                short message_len = 0;
                memcpy(&message_len, response_head, HEAD_LENGTH);
                message_len = asio::detail::socket_ops::network_to_host_short(message_len);
                char message[MAX_LENGTH] {};
                asio::read(
                    socket,
                    asio::buffer(message, message_len)
                );

                std::cout << "response len: " << message_len << std::endl;
                std::cout << "response: " << message << std::endl;
            }
        });

        send_thread.join();
        rece_thraed.join();

    } catch (std::exception &exp) {
        std::cerr << exp.what() << std::endl;
    }
    return 0;
}