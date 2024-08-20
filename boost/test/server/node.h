#ifndef _NODE_H_
#define _NODE_H_

/**
 * +----+-----+---------+
 * | id | len |  value  |
 * +----+-----+---------+
 * |   head   |   data  |
 * +----------+---------+
 *                      |
 *                  total_len
 */

typedef short NODE_ID_TYPE;
typedef short NODE_LEN_TYPE;
typedef char *NODE_DATA_TYPE;

extern const short NODE_ID_SIZE;
extern const short NODE_LEN_SIZE;
extern const short NODE_HEAD_SIZE;


/**
 * host endianness to network endianness
 */
class SendNode {
public:
    SendNode(short id, short len, const char *buf);
    ~SendNode();

    short getHostId() const;
    short getHostDataLen() const;
    char *getData() const;
    short getTotalLen() const;
    void clear();

private:
    NODE_ID_TYPE host_id_;
    NODE_LEN_TYPE host_data_len_;
    NODE_DATA_TYPE data_;   // [network_id, network_len, message]
    short total_len_;
};

/**
 * network endianness to host endianness
 */
class RecvNodeHead {
public:
    RecvNodeHead();
    ~RecvNodeHead();

    short getHostId();
    short getHostDataLen();
    char *getData() const;
    void clear();

private:
    NODE_ID_TYPE host_id_;
    NODE_LEN_TYPE host_data_len_;
    NODE_DATA_TYPE data_;
};

/**
 * network endianness to host endianness
 */
class RecvNodeData {
public:
    RecvNodeData(short len);
    ~RecvNodeData();

    char *getData() const;
    short getTotalLen();
    void clear();

private:
    NODE_DATA_TYPE data_;
    short total_len_;
};

#endif // _NODE_H_