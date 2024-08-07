#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>

#define MAX_MESSAGE_LEN 1024

namespace asio = boost::asio;

using SocketSPtr = std::shared_ptr<asio::ip::tcp::socket>;
using ThreadSPtr = std::shared_ptr<std::thread>;

std::vector<std::thread> threads;

void session(SocketSPtr socket) {
    try {
        for (;;) {
            char data[MAX_MESSAGE_LEN] {};
            boost::system::error_code error;
            // std::size_t receive_len = asio::read(*socket, asio::buffer(data, MAX_MESSAGE_LEN));
            std::size_t receive_len = socket->read_some(
                asio::buffer(data, MAX_MESSAGE_LEN),
                error
            );
            if (error == asio::error::eof) {
                std::cerr << "peer closed" << std::endl;
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout << "from " << socket->remote_endpoint().address().to_string() << std::endl;
            std::cout << "receive: " << data << std::endl;
        }
    } catch (std::exception &err) {
        std::cerr << "session " << err.what() << std::endl;
    }
}

void server(asio::io_context &ioc, unsigned short port) {
    asio::ip::tcp::acceptor acceptor(
        ioc, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)
    );
    for (;;) {
        // acceptor 接收 socket 连接
        std::cout << "acceptor receive" << std::endl;
        SocketSPtr socket = std::make_shared<asio::ip::tcp::socket>(ioc);
        boost::system::error_code err;
        acceptor.accept(*socket, err);
        if (err) {
            std::cerr << "accept error" << std::endl;
            continue;
        }
        std::thread t(session, socket);
        threads.push_back(std::move(t));
    }
}

int main(int argc, char *argv[]) {
    try {
        asio::io_context ioc;
        unsigned short port = 11451;
        server(ioc, port);
        for (auto &t : threads) {
            // t->join();
            t.join();
        }
    } catch (std::exception &e) {
        std::cerr << "main " << e.what() << std::endl;
    }
    return 0;
}

// #include <boost/asio.hpp>
// #include <iostream>
// #include <vector>
// #include <thread>

// #define MAX_MESSAGE_LEN 1024

// namespace asio = boost::asio;

// std::vector<std::thread> threads;

// void session(asio::ip::tcp::socket socket) {
//     try {
//         for (;;) {
//             char data[MAX_MESSAGE_LEN] {};
//             boost::system::error_code error;
//             std::size_t receive_len = socket.read_some(
//                 asio::buffer(data, MAX_MESSAGE_LEN),
//                 error
//             );
//             if (error == asio::error::eof) {
//                 std::cerr << "peer closed" << std::endl;
//                 break;
//             } else if (error) {
//                 throw boost::system::system_error(error);
//             }

//             std::cout << "from " << socket.remote_endpoint().address().to_string() << std::endl;
//             std::cout << "receive: " << data << std::endl;
//         }
//     } catch (std::exception &err) {
//         std::cerr << "session " << err.what() << std::endl;
//     }
// }

// void server(asio::io_context &ioc, unsigned short port) {
//     asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
//     asio::ip::tcp::acceptor acceptor(ioc, endpoint);
//     for (;;) {
//         asio::ip::tcp::socket socket(ioc);
//         boost::system::error_code err;
//         acceptor.accept(socket, err);
//         if (err) {
//             std::cerr << "accept error" << std::endl;
//             continue;
//         }
//         threads.emplace_back(
//             std::thread(session, std::move(socket))
//         );
//     }
// }

// int main(int argc, char *argv[]) {
//     try {
//         asio::io_context ioc;
//         unsigned short port = 11451;
//         server(ioc, port);
//         for (auto &t : threads) {
//             t.join();
//         }
//     } catch (std::exception &e) {
//         std::cerr << "main " << e.what() << std::endl;
//     }
//     return 0;
// }