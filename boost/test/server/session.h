#ifndef _SESSION_H_
#define _SESSION_H_

#include "node.h"
#include <boost/asio.hpp>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#define MAX_SEND_QUE_SIZE 1000
#define MAX_NODE_DATA_SIZE 1024 * 2

namespace asio = boost::asio;

class Server;

class Session :
    public std::enable_shared_from_this<Session> {

public:
    Session(asio::io_context &ioc, Server *server);
    ~Session();

    const std::string &getUuid() const;
    asio::ip::tcp::socket &getClientSocket();

    void startRecv();
    void send(short id, short len, const char *buf);

private:
    void handleRecvHead(
        boost::system::error_code err_code,
        std::size_t bytes_transferred,
        std::shared_ptr<Session> self
    );
    void handleRecvData(
        boost::system::error_code err_code,
        std::size_t bytes_transferred,
        std::shared_ptr<Session> self
    );
    void handleSend(
        boost::system::error_code err_code,
        std::size_t bytes_transferred,
        std::shared_ptr<Session> self
    );

    asio::ip::tcp::socket client_socket_;
    Server *server_;
    std::string uuid_;

    /* send */
    std::mutex send_mutex;
    std::queue<std::shared_ptr<SendNode>> send_que_;

    /* receive */
    std::shared_ptr<RecvNodeHead> recv_head_node_;
    std::shared_ptr<RecvNodeData> recv_data_node_;
};

#endif // _SESSION_H_