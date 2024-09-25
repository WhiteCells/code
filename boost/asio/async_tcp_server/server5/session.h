#ifndef _SESSION_H_
#define _SESSION_H_

#include "node.h"
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <mutex>
#include <queue>

#define MAX_SEND_QUE_SIZE     1000
#define MAX_NODE_MESSAGE_SIZE 1024 * 2

namespace asio = boost::asio;

class Server;

class Session :
    public std::enable_shared_from_this<Session>
{
public:
    Session(asio::io_context &ioc, Server *server);
    ~Session();

    const std::string &getUuid() const;
    asio::ip::tcp::socket &getClientSocket();

    void send(short id, short len, const char *buf);
    void start();

private:
    void handleWrite(
        boost::system::error_code err_code,
        std::shared_ptr<Session> self);
    void handleReadHead(
        boost::system::error_code err_code,
        std::size_t bytes_transferred,
        std::shared_ptr<Session> self);
    void handleReadMessage(
        boost::system::error_code err_code,
        std::size_t bytes_transferred,
        std::shared_ptr<Session> self);

    // used for communication
    asio::ip::tcp::socket client_socket_;
    // server to call `server->removeSession()`
    Server *server_;
    // Session uuid identification
    std::string uuid_;

    /* send */
    std::mutex send_mutex_;
    std::queue<std::shared_ptr<SendNode>> send_que_;

    /* receive */
    std::shared_ptr<RecvNodeHead> head_node_;
    std::shared_ptr<RecvNodeMessage> message_node_;
};

#endif // _SESSION_H_