#include "session.h"
#include "server.h"
#include "logic_system.h"
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>

Session::Session(asio::io_context &ioc, Server *server) :
    client_socket_(ioc),
    server_(server) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string uuid_str = boost::uuids::to_string(uuid);
    uuid_ = uuid_str;
}

Session::~Session() {
    std::cout << "~Session()" << std::endl;
}

const std::string &Session::getUuid() const {
    return uuid_;
}

asio::ip::tcp::socket &Session::getClientSocket() {
    return client_socket_;
}

void Session::send(short id, short len, const char *buf) {
    std::lock_guard<std::mutex> lock(send_mutex_);
    int send_que_size = send_que_.size();
    if (send_que_size > MAX_SEND_QUE_SIZE) {
        std::cerr << "send queue is full" << std::endl;
        return;
    }
    send_que_.emplace(std::make_shared<SendNode>(id, len, buf));
    if (send_que_size > 0) {
        return;
    }
    // front
    auto &front_send_node = send_que_.front();
    asio::async_write(
        client_socket_,
        asio::buffer(front_send_node->data_, front_send_node->total_len_),
        std::bind(
            &Session::handleWrite,
            this,
            std::placeholders::_1,
            shared_from_this()
        )
    );
}

void Session::start() {
    head_node_ = std::make_shared<RecvNodeHead>();
    asio::async_read(
        client_socket_,
        asio::buffer(head_node_->data_, NODE_HEAD_SIZE),
        std::bind(
            &Session::handleReadHead,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            shared_from_this()
        )
    );
}

void Session::handleWrite(
    boost::system::error_code err_code,
    std::shared_ptr<Session> self
) {
    if (err_code) {
        std::cerr << "handle write error value: " << err_code.value() << std::endl;
        std::cerr << "handle write error message: " << err_code.message() << std::endl;
        server_->removeSession(uuid_);
        return;
    }

    std::lock_guard<std::mutex> lock(send_mutex_);

    std::cout << "send id: " << send_que_.front()->host_id_ << std::endl;
    std::cout << "send len: " << send_que_.front()->host_len_ << std::endl;
    std::cout << "send data: " << send_que_.front()->data_ + NODE_HEAD_SIZE << std::endl;

    send_que_.pop();

    if (!send_que_.empty()) {
        auto &front_send_node = send_que_.front();
        asio::async_write(
            client_socket_,
            asio::buffer(front_send_node->data_, front_send_node->total_len_),
            std::bind(
                &Session::handleWrite,
                this,
                std::placeholders::_1,
                self
            )
        );
    }
}

void Session::handleReadHead(
    boost::system::error_code err_code,
    std::size_t bytes_transferred,
    std::shared_ptr<Session> self
) {
    if (err_code) {
        std::cerr << "handle write error value: " << err_code.value() << std::endl;
        std::cerr << "handle write error message: " << err_code.message() << std::endl;
        server_->removeSession(uuid_);
        return;
    }

    std::cout << "read head finished, " << bytes_transferred << std::endl;

    short id = head_node_->getHostId();
    short len = head_node_->getHostLen();
    std::cout << "recv id: " << id << std::endl;
    std::cout << "recv len: " << len << std::endl;

    if (len > MAX_NODE_MESSAGE_SIZE) {
        std::cerr << "the message body is too long" << std::endl;
        server_->removeSession(uuid_);
        return;
    }

    message_node_ = std::make_shared<RecvNodeMessage>(len);
    asio::async_read(
        client_socket_,
        asio::buffer(message_node_->data_, len),
        std::bind(
            &Session::handleReadMessage,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            self
        )
    );
}

void Session::handleReadMessage(
    boost::system::error_code err_code,
    std::size_t bytes_transferred,
    std::shared_ptr<Session> self
) {
    if (err_code) {
        std::cerr << "handle write error value: " << err_code.value() << std::endl;
        std::cerr << "handle write error message: " << err_code.message() << std::endl;
        server_->removeSession(uuid_);
        return;
    }
    std::cout << "read messaged finished, " << bytes_transferred << std::endl;
    std::cout << "recv message: " << message_node_->data_ << std::endl;

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    LogicSystem::getInstance()->pushMessageToQueue(
        std::make_shared<LogicNode>(head_node_->getHostId(), message_node_, self)
    );

    start();

    // head_node_->clear();
    // asio::async_read(
    //     client_socket_,
    //     asio::buffer(head_node_->data_, NODE_HEAD_SIZE),
    //     std::bind(
    //         &Session::handleReadHead,
    //         this,
    //         std::placeholders::_1,
    //         std::placeholders::_2,
    //         self
    //     )
    // );
}