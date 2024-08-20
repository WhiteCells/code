#include "node.h"
#include <cstring>
#include <arpa/inet.h>
#include <iostream>

SendNode::SendNode(short id, short len, const char *buf) :
    id_(id),
    len_(len),
    total_len_(NODE_HEAD_SIZE + len),
    processed_len_(0) {

    data_ = new char[total_len_ + 1] {};
    short id_network = htons(id_);
    short len_network = htons(len_);
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

}

RecvNodeHead::RecvNodeHead() {
    data_ = new char[NODE_HEAD_SIZE] {};
}

RecvNodeHead::~RecvNodeHead() {
    std::cout << "~RecvNodeHead()" << std::endl;
    delete[] data_;
}

NODE_ID_TYPE RecvNodeHead::getId() const {
    NODE_ID_TYPE id = 0;
    memcpy(&id, data_, NODE_ID_SIZE);
    return ntohs(id);
}

NODE_LEN_TYPE RecvNodeHead::getLen() const {
    NODE_LEN_TYPE len = 0;
    memcpy(&len, data_ + NODE_ID_SIZE, NODE_LEN_SIZE);
    return ntohs(len);
}

void RecvNodeHead::clear() {
    memset(data_, 0, NODE_HEAD_SIZE);
}

RecvNodeMessage::RecvNodeMessage(short len) : len_(len) {
    data_ = new char[len + 1] {};
    data_[len] = '\0';
}

RecvNodeMessage::~RecvNodeMessage() {
    std::cout << "~RecvNodeMessage()" << std::endl;
    delete[] data_;
}

char *RecvNodeMessage::getMessage() {
    return data_;
}

void RecvNodeMessage::clear() {
    memset(data_, 0, len_ + 1);
}