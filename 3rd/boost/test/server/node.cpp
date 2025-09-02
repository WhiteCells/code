#include "node.h"
#include <boost/asio/detail/socket_ops.hpp>
#include <cstring>
#include <iostream>

using boost::asio::detail::socket_ops::host_to_network_short;
using boost::asio::detail::socket_ops::network_to_host_short;

const short NODE_ID_SIZE = sizeof(NODE_ID_TYPE);
const short NODE_LEN_SIZE = sizeof(NODE_LEN_TYPE);
const short NODE_HEAD_SIZE = NODE_ID_SIZE + NODE_LEN_SIZE;

SendNode::SendNode(short id, short len, const char *buf) :
    host_id_(id),
    host_data_len_(len),
    total_len_(NODE_HEAD_SIZE + len) {

    data_ = new char[total_len_ + 1] {};
    short network_id = host_to_network_short(id);
    short network_len = host_to_network_short(len);
    memcpy(data_, &network_id, NODE_ID_SIZE);
    memcpy(data_ + NODE_ID_SIZE, &network_len, NODE_LEN_SIZE);
    memcpy(data_ + NODE_HEAD_SIZE, buf, len);
    data_[total_len_] = '\0';
}

SendNode::~SendNode() {
    std::cout << __func__ << std::endl;
    delete[] data_;
}

short SendNode::getHostId() const {
    return host_id_;
}

short SendNode::getHostDataLen() const {
    return host_data_len_;
}

char *SendNode::getData() const {
    return data_;
}

short SendNode::getTotalLen() const {
    return total_len_;
}

void SendNode::clear() {
    memset(data_, 0, total_len_);
}

RecvNodeHead::RecvNodeHead() :
    host_id_(-1),
    host_data_len_(-1) {
    data_ = new char[NODE_HEAD_SIZE] {};
}

RecvNodeHead::~RecvNodeHead() {
    delete[] data_;
}

short RecvNodeHead::getHostId() {
    if (-1 == host_id_) {
        memcpy(&host_id_, data_, NODE_ID_SIZE);
        host_id_ = network_to_host_short(host_id_);
    }
    return host_id_;
}

short RecvNodeHead::getHostDataLen() {
    if (-1 == host_data_len_) {
        memcpy(&host_data_len_, data_ + NODE_ID_SIZE, NODE_LEN_SIZE);
        host_data_len_ = network_to_host_short(host_data_len_);
    }
    return host_data_len_;
}

char *RecvNodeHead::getData() const {
    return data_;
}

void RecvNodeHead::clear() {
    memset(data_, 0, NODE_HEAD_SIZE);
}

RecvNodeData::RecvNodeData(short len) :
    total_len_(len) {
    data_ = new char[len + 1] {};
    data_[len] = '\0';
}

RecvNodeData::~RecvNodeData() {
    delete[] data_;
}

char *RecvNodeData::getData() const {
    return data_;
}

void RecvNodeData::clear() {
    memset(data_, 0, total_len_);
}