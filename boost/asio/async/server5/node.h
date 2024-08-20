#ifndef _NODE_H_
#define _NODE_H_

#include <memory>

class Session;

typedef short NODE_ID_TYPE;
typedef short NODE_LEN_TYPE;

extern const short NODE_ID_SIZE;
extern const short NODE_LEN_SIZE;
extern const short NODE_HEAD_SIZE;

/**
 * TLV
 * +----------+--------+----------+
 * | type(id) | length |  value   |
 * +----------+--------+----------+
 * |        head       |  message |
 * +-------------------+----------+
 * 
 * +---------+---------------+
 * |         |               |
 * +---------+---------------+
 *           |               |
 *      processed_len    total_len
 */

/**
 * host to network endianness
 */
class SendNode {
public:
    SendNode(short id, short len, const char *buf);
    ~SendNode();

    void clear();

    NODE_ID_TYPE host_id_;    // host endianness
    NODE_LEN_TYPE host_len_;  // host endianness
    char *data_;              // storage [id(network) len(network) message]
    short total_len_;
    short processed_len_;
};

/**
 * network to host endianness
 */
class RecvNodeHead {
public:
    RecvNodeHead();
    ~RecvNodeHead();

    NODE_ID_TYPE getHostId() const;
    NODE_ID_TYPE getHostLen() const;

    void clear();

    char *data_;
};

class RecvNodeMessage {
public:
    RecvNodeMessage(short len);
    ~RecvNodeMessage();

    char *getMessage() const;
    void clear();

    int len_;
    char *data_;
};

class LogicNode {
public:
    LogicNode(
        NODE_ID_TYPE id,
        std::shared_ptr<RecvNodeMessage> recv_node_message,
        std::shared_ptr<Session> session
    );
    ~LogicNode();

    NODE_ID_TYPE getId() const;
    std::shared_ptr<RecvNodeMessage> getRecvNodeMessage();
    std::shared_ptr<Session> getSession();

private:
    NODE_ID_TYPE id_;
    std::shared_ptr<RecvNodeMessage> recv_node_message_;
    std::shared_ptr<Session> session_;
};

#endif // _NODE_H_