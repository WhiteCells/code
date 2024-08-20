#ifndef _NODE_H_
#define _NODE_H_

typedef short NODE_ID_TYPE;
typedef short NODE_LEN_TYPE;

inline const short NODE_ID_SIZE = sizeof(NODE_ID_TYPE);
inline const short NODE_LEN_SIZE = sizeof(NODE_LEN_TYPE);
inline const short NODE_HEAD_SIZE = NODE_ID_SIZE + NODE_LEN_SIZE;

/**
 * TLV
 * +----------+--------+----------+
 * | type(id) | length |  value   |
 * +----------+--------+----------+
 * |        head       |  message |
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

    NODE_ID_TYPE id_;    // host
    NODE_LEN_TYPE len_;  // host
    char *data_;         // storage network
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

    NODE_ID_TYPE getId() const;
    NODE_ID_TYPE getLen() const;

    void clear();

    char *data_;
};

class RecvNodeMessage {
public:
    RecvNodeMessage(short len);
    ~RecvNodeMessage();

    char *getMessage();
    void clear();

    int len_;
    char *data_;
};

#endif // _NODE_H_