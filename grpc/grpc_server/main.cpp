#include "grpc_service.h"
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

int main(int argc, char *argv[])
{
    GrpcService grpc_service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort("127.0.0.1:11451",
                             grpc::InsecureServerCredentials());
    builder.RegisterService(&grpc_service);
    std::unique_ptr<grpc::Server> grpc_server(builder.BuildAndStart());
    std::cout << "Grpc Server listening: " << "127.0.0.1:11451" << std::endl;

    boost::asio::io_context ioc;
    boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&grpc_server, &ioc](boost::system::error_code err_code, int signal_num) {
        if (!err_code) {
            std::cout << "Shutting down Grpc Server" << std::endl;
            grpc_server->Shutdown();
            ioc.stop();
        }
    });

    std::thread([&ioc]() {
        ioc.run();
    }).detach();

    grpc_server->Wait();
    return 0;
}