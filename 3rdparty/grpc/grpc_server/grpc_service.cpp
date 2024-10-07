#include "grpc_service.h"

GrpcService::GrpcService()
{
}

grpc::Status GrpcService::getNode(
    grpc::ServerContext *context,
    const node::RequestNode *req_node,
    node::ResponseNode *rsp_node)
{
    if (req_node->id() == 1) {
        rsp_node->set_error(0);
        rsp_node->set_data(req_node->data().c_str());
        return grpc::Status::OK;
    }
    return grpc::Status::CANCELLED;
}