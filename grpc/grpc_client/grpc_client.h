#ifndef _GRPC_CLIENT_H_
#define _GRPC_CLIENT_H_

#include "proto/node.grpc.pb.h"
#include "grpc_connection_pool.hpp"

class GrpcClient
{
public:
    ~GrpcClient();

    static GrpcClient &getInstance();
    node::ResponseNode getNode(int id, int len, std::string data);

private:
    GrpcClient();
    GrpcClient(const GrpcClient &) = delete;
    GrpcClient(GrpcClient &&) = delete;
    GrpcClient &operator=(const GrpcClient &) = delete;
    GrpcClient &operator=(GrpcClient &&) = delete;

    std::shared_ptr<GrpcConnectionPool<node::DataServer::Stub>> grpc_connection_pool_;
};

#endif // _GRPC_CLIENT_H_