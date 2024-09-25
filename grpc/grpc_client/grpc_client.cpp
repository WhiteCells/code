#include "grpc_client.h"
#include "grpc_connection_pool.hpp"
#include <thread>

GrpcClient::~GrpcClient()
{
    grpc_connection_pool_->stopAllConnection();
}

GrpcClient &GrpcClient::getInstance()
{
    static GrpcClient grpc_client;
    return grpc_client;
}

node::ResponseNode GrpcClient::getNode(
    int id,
    int len,
    std::string data)
{
    grpc::ClientContext context;
    node::RequestNode req_node;
    node::ResponseNode rsp_node;
    req_node.set_id(1);
    req_node.set_len(10);
    req_node.set_data(data.c_str());

    std::unique_ptr<node::DataServer::Stub> stub = grpc_connection_pool_->getConnection();
    grpc::Status status = stub->getNode(&context, req_node, &rsp_node);
    if (!status.ok()) {
        rsp_node.set_error(1);
    }
    grpc_connection_pool_->recycleConnection(std::move(stub));
    return rsp_node;
}

GrpcClient::GrpcClient()
{
    grpc_connection_pool_ = std::make_shared<GrpcConnectionPool<node::DataServer::Stub>>(
        std::thread::hardware_concurrency(),
        std::string("127.0.0.1"),
        std::string("11451"));
}
