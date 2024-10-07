#ifndef _GRPC_SERVICE_H_
#define _GRPC_SERVICE_H_

#include "proto/node.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class GrpcService final : public node::DataServer::Service
{
public:
    GrpcService();

    virtual grpc::Status getNode(
        grpc::ServerContext *context,
        const node::RequestNode *req_node,
        node::ResponseNode *rsp_node) override;
};

#endif // _GRPC_SERVICE_H_