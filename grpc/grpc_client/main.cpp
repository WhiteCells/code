#include "grpc_client.h"
#include <iostream>

int main(int argc, char *argv[])
{
    node::ResponseNode rsp_node = GrpcClient::getInstance().getNode(1, 5, "hello1");
    if (!rsp_node.error()) {
        std::cout << rsp_node.data() << std::endl;
    }

    rsp_node = GrpcClient::getInstance().getNode(1, 5, "hello2");
    if (!rsp_node.error()) {
        std::cout << rsp_node.data() << std::endl;
    }

    rsp_node = GrpcClient::getInstance().getNode(1, 5, "hello3");
    if (!rsp_node.error()) {
        std::cout << rsp_node.data() << std::endl;
    }
    return 0;
}