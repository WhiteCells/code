#include "server.h"
#include "io_context_pool.h"
// #include "io_thread_pool.h"
#include <iostream>

Server::Server(asio::io_context &ioc, unsigned short port) :
    ioc_(ioc),
    // acceptor_(ioc_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    acceptor_(ioc_, {asio::ip::tcp::v4(), port})
{
    startAccept();
}

Server::~Server()
{
}

// receiving new connections is
// also a function that needs to be executed after
// successfully receiving new connections in order to receive them
void Server::startAccept()
{
    // IoContextPool get io_context
    asio::io_context &ioc = IoContextPool::getInstance().getIoContext();
    // asio::io_context &ioc = IoThreadPool::getInstance().getIoContext();
    std::shared_ptr<Session> session = std::make_shared<Session>(ioc, this);
    acceptor_.async_accept(
        session->getClientSocket(),
        std::bind(
            &Server::handleAccept,
            this,
            std::placeholders::_1,
            session));
}

// session use_count() - 1
void Server::removeSession(const std::string &uid)
{
    sessions_.erase(uid);
}

// callback after receiving a new connection
void Server::handleAccept(
    const boost::system::error_code &err_code,
    std::shared_ptr<Session> session)
{
    if (err_code) {
        std::cerr << "accept error value: " << err_code.value() << std::endl;
        std::cerr << "accept error message: " << err_code.message() << std::endl;
        return;
    }

    std::cout << "client ip: " << session->getClientSocket().remote_endpoint().address().to_string() << std::endl;

    session->start();

    // sessions_ manage session
    sessions_.insert({session->getUuid(), session});

    // accept new connection
    startAccept();
}

// boost asio caught signal
int main(int argc, char *argv[])
{
    try {
        asio::io_context ioc;
        Server server(ioc, 10101);
        asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const boost::system::error_code &err_code, int signal_num) {
            if (err_code) {
                std::cerr << "err value: " << err_code.value() << std::endl;
                std::cerr << "err message: " << err_code.message() << std::endl;
                return;
            }
            std::cout << "signal caught: " << signal_num << std::endl;
            ioc.stop();
        });
        ioc.run();
    }
    catch (const std::exception &exp) {
        std::cerr << "exception: " << exp.what() << std::endl;
    }
    return 0;
}

// POSIX
// #include <csignal>
// #include <thread>
// #include <mutex>
// #include <condition_variable>

// bool need_stopping = false;
// std::mutex quit_mutex;
// std::condition_variable quit_condition;

// void handleSignal(int signal_num) {
//     if (signal_num == SIGINT || signal_num == SIGTERM) {
//         std::unique_lock<std::mutex> ulock(quit_mutex);
//         need_stopping = true;
//         ulock.unlock();
//         // {
//         //     std::lock_guard<std::mutex> lock(quit_mutex);
//         //     need_stopping = true;
//         // }
//         std::cout << "signal caught" << signal_num << std::endl;
//         // only one consumer is needed to handle the ioc.stop()
//         quit_condition.notify_one();
//     }
// }

// caught signal in sub thread
// int main(int argc, char *argv[]) {
//     try {
//         asio::io_context ioc;
//         std::thread caught_signal_thread([&ioc]() {
//             signal(SIGINT, handleSignal);
//             signal(SIGTERM, handleSignal);
//             std::unique_lock<std::mutex> ulock(quit_mutex);
//             quit_condition.wait(ulock, []() {
//                 return need_stopping;
//             });
//             // while (!need_stopping) {
//             //     std::unique_lock<std::mutex> ulokc(quit_mutex);
//             //     quit_condition.wait(ulock);
//             // }
//             ioc.stop();
//         });
//         Server server(ioc, 10101);
//         ioc.run();
//         caught_signal_thread.join();
//     } catch (std::exception &exp) {
//         std::cout << "exception: " << exp.what() << std::endl;
//     }
//     return 0;
// }

// caught signal in main thread
// int main(int argc, char *argv[]) {
//     try {
//         asio::io_context ioc;
//         std::thread server_thread([&ioc]() {
//             Server server(ioc, 10101);
//             ioc.run();
//         });

//         signal(SIGINT, handleSignal);
//         signal(SIGTERM, handleSignal);

//         std::unique_lock<std::mutex> ulock(quit_mutex);
//         quit_condition.wait(ulock, []() {
//             return need_stopping;
//         });
//         ioc.stop();
//         server_thread.join();
//     } catch (std::exception &exp) {
//         std::cout << "exception: " << exp.what() << std::endl;
//     }
//     return 0;
// }