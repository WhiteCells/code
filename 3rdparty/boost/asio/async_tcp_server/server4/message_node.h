#ifndef _MESSAGE_NODE_H_
#define _MESSAGE_NODE_H_

#define HEAD_LENGTH 2

class MessageNode {
    friend class Session;

public:
    MessageNode(short len);
    MessageNode(const char *buf, short len);
    ~MessageNode();

    void clear();

protected:
    short total_len_;
    short processed_len_;
    char *data_;
};

class ReceiveNode : public MessageNode {
public:
    ReceiveNode(short len);
    ~ReceiveNode();
};

class SendNode {
public:
    SendNode(const char *buf, short len);
    ~SendNode();
};

#endif // _MESSAGE_NODE_H_