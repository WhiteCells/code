#include "message_node.h"
#include <cstring>

MessageNode::MessageNode(short len) :
    total_len_(len + HEAD_LENGTH) {
    data_ = new char[total_len_ + 1];
    memset(data_, 0, total_len_);
}

MessageNode::MessageNode(const char *buf, short len) :
    total_len_(len + HEAD_LENGTH),
    processed_len_(0) {
    data_ = new char[total_len_ + 1];
    memcpy(data_, &len, HEAD_LENGTH);
    memcpy(data_ + HEAD_LENGTH, buf, len);
    data_[total_len_] = '\0';
}

MessageNode::~MessageNode() {
    if (data_) {
        delete[] data_;
        data_ = nullptr;
    }
}

void MessageNode::clear() {
    if (data_) {
        memset(data_, 0, total_len_);
        processed_len_ = 0;
    }
}
