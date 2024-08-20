#include "node.h"
#include <boost/asio.hpp>
#include <thread>
#include <iostream>

typedef short NODE_ID_TYPE;
typedef short NODE_LEN_TYPE;

#define NODE_ID_SIZE sizeof(NODE_ID_TYPE)
#define NODE_LEN_SIZE sizeof(NODE_LEN_TYPE)

namespace asio = boost::asio;

int main(int argc, char *argv[]) {
    try {
        std::string ip_str = "127.0.0.1";
        asio::ip::address ip = asio::ip::address::from_string(ip_str);
        unsigned short port = 10101;
        asio::ip::tcp::endpoint endpoint(ip, port);
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc);
        boost::system::error_code err_code;
        socket.connect(endpoint, err_code);
        if (err_code) {
            std::cerr << "err value: " << err_code.value() << std::endl;
            std::cerr << "err message: " << err_code.message() << std::endl;
            return EXIT_FAILURE;
        }

        // send thread
        std::thread send_thread([&socket]() {
            for (;;) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::shared_ptr<SendNode> send_node = std::make_shared<SendNode>(10101, 5, "white");
                asio::write(
                    socket,
                    asio::buffer(
                        send_node->data_,
                        send_node->total_len_
                    )
                );
                std::cout << "send id: " << send_node->id_ << std::endl;
                std::cout << "send len: " << send_node->len_ << std::endl;
                std::cout << "send message: " << send_node->data_ + NODE_HEAD_SIZE << std::endl;
            }
        });

        // receive thread
        std::thread recv_thread([&socket]() {
            for (;;) {
                std::shared_ptr<RecvNodeHead> head_node = std::make_shared<RecvNodeHead>();
                asio::read(
                    socket,
                    asio::buffer(head_node->data_, NODE_HEAD_SIZE)
                );
                std::cout << "recv id: " << head_node->getId() << std::endl;
                std::cout << "recv len: " << head_node->getLen() << std::endl;

                std::shared_ptr<RecvNodeMessage> message_node = std::make_shared<RecvNodeMessage>(head_node->getLen());
                asio::read(
                    socket,
                    asio::buffer(message_node->data_, head_node->getLen())
                );
                std::cout << "recv message: " << message_node->getMessage() << std::endl;
            }
        });

        send_thread.join();
        recv_thread.join();

    } catch (const boost::system::system_error &err) {
        std::cerr << "err code: " << err.code() << std::endl;
        std::cerr << "err what: " << err.what() << std::endl;
    }
    return 0;
}