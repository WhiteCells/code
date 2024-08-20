#include "node.h"
#include <cstring>
#include <arpa/inet.h>
#include <iostream>

const short NODE_ID_SIZE = sizeof(NODE_ID_TYPE);
const short NODE_LEN_SIZE = sizeof(NODE_LEN_TYPE);
const short NODE_HEAD_SIZE = NODE_ID_SIZE + NODE_LEN_SIZE;

SendNode::SendNode(short id, short len, const char *buf) :
    host_id_(id),
    host_len_(len),
    total_len_(NODE_HEAD_SIZE + len),
    processed_len_(0) {

    short id_network = htons(host_id_);
    short len_network = htons(host_len_);
    data_ = new char[total_len_ + 1] {};
    memcpy(data_, &id_network, NODE_ID_SIZE);
    memcpy(data_ + NODE_ID_SIZE, &len_network, NODE_LEN_SIZE);
    memcpy(data_ + NODE_HEAD_SIZE, buf, len);
    data_[total_len_] = '\0';
}

SendNode::~SendNode() {
    std::cout << "~SendNode()" << std::endl;
    delete[] data_;
}

void SendNode::clear() {
    memset(data_, 0, total_len_);
    processed_len_ = 0;
}

RecvNodeHead::RecvNodeHead() {
    data_ = new char[NODE_HEAD_SIZE] {};
}

RecvNodeHead::~RecvNodeHead() {
    std::cout << "~RecvNodeHead()" << std::endl;
    delete[] data_;
}

NODE_ID_TYPE RecvNodeHead::getHostId() const {
    NODE_ID_TYPE id = 0;
    memcpy(&id, data_, NODE_ID_SIZE);
    return ntohs(id);
}

NODE_LEN_TYPE RecvNodeHead::getHostLen() const {
    NODE_LEN_TYPE len = 0;
    memcpy(&len, data_ + NODE_ID_SIZE, NODE_LEN_SIZE);
    return ntohs(len);
}

void RecvNodeHead::clear() {
    memset(data_, 0, NODE_HEAD_SIZE);
}

RecvNodeMessage::RecvNodeMessage(short len) : len_(len) {
    data_ = new char[len + 1];
    data_[len] = '\0';
}

RecvNodeMessage::~RecvNodeMessage() {
    std::cout << "~RecvNodeMessage()" << std::endl;
    delete[] data_;
}

char *RecvNodeMessage::getMessage() const {
    return data_;
}

void RecvNodeMessage::clear() {
    memset(data_, 0, len_ + 1);
}

LogicNode::LogicNode(
    NODE_ID_TYPE id,
    std::shared_ptr<RecvNodeMessage> recv_node_message,
    std::shared_ptr<Session> session
) :
    id_(id),
    recv_node_message_(recv_node_message),
    session_(session) {

}

LogicNode::~LogicNode() {

}

NODE_ID_TYPE LogicNode::getId() const {
    return id_;
}

std::shared_ptr<RecvNodeMessage> LogicNode::getRecvNodeMessage() {
    return recv_node_message_;
}

std::shared_ptr<Session> LogicNode::getSession() {
    return session_;
}