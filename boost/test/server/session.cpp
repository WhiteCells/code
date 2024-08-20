#include "session.h"
#include "server.h"
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>

Session::Session(asio::io_context &ioc, Server *server) :
    client_socket_(ioc),
    server_(server) {

    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    uuid_ = boost::uuids::to_string(uuid);
}

Session::~Session() {

}

const std::string &Session::getUuid() const {
    return uuid_;
}

asio::ip::tcp::socket &Session::getClientSocket() {
    return client_socket_;
}


void Session::startRecv() {
    recv_head_node_ = std::make_shared<RecvNodeHead>();
    asio::async_read(
        client_socket_,
        asio::buffer(
            recv_head_node_->getData(),
            NODE_HEAD_SIZE
        ),
        std::bind(
            &Session::handleRecvHead,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            shared_from_this()
        )
    );
}

void Session::send(short id, short len, const char *buf) {
    std::lock_guard<std::mutex> lock(send_mutex);
    std::size_t send_que_size = send_que_.size();
    if (send_que_size > MAX_SEND_QUE_SIZE) {
        std::cerr << "queue is full" << std::endl;
        return;
    }
    send_que_.emplace(std::make_shared<SendNode>(id, len, buf));
    if (send_que_size > 0) {
        return;
    }
    auto send_node = send_que_.front();
    asio::async_write(
        client_socket_,
        asio::buffer(
            send_node->getData(),
            send_node->getTotalLen()
        ),
        std::bind(
            &Session::handleSend,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            shared_from_this()
        )
    );
}

void Session::handleRecvHead(
    boost::system::error_code err_code,
    std::size_t bytes_transferred,
    std::shared_ptr<Session> self
) {
    if (err_code) {
        std::cerr << "err value: " << err_code.value() << std::endl;
        std::cerr << "err message: " << err_code.message() << std::endl;
        server_->removeSession(uuid_);
        return;
    }

    assert(NODE_HEAD_SIZE == bytes_transferred);

    short id = recv_head_node_->getHostId();
    short data_len = recv_head_node_->getHostDataLen();
    std::cout << "recv id: " << id << std::endl;
    std::cout << "recv data len: " << data_len << std::endl;

    if (data_len > MAX_NODE_DATA_SIZE) {
        std::cerr << "recv data to long" << std::endl;
        server_->removeSession(uuid_);
        return;
    }

    recv_data_node_ = std::make_shared<RecvNodeData>(data_len);
    asio::async_read(
        client_socket_,
        asio::buffer(
            recv_data_node_->getData(),
            data_len
        ),
        std::bind(
            &Session::handleRecvData,
            this,
            std::placeholders::_1,
            std::placeholders::_2,
            self
        )
    );
}

void Session::handleRecvData(
    boost::system::error_code err_code,
    std::size_t bytes_transferred,
    std::shared_ptr<Session> self
) {
    if (err_code) {
        std::cerr << "err value: " << err_code.value() << std::endl;
        std::cerr << "err message: " << err_code.message() << std::endl;
        server_->removeSession(uuid_);
        return;
    }

    assert(recv_head_node_->getHostDataLen() == bytes_transferred);

    const char *data = recv_data_node_->getData();
    std::cout << "recv data: " << data << std::endl;

    startRecv();
}

void Session::handleSend(
    boost::system::error_code err_code,
    std::size_t bytes_transferred,
    std::shared_ptr<Session> self
) {
    if (err_code) {
        std::cerr << "err value: " << err_code.value() << std::endl;
        std::cerr << "err message: " << err_code.message() << std::endl;
        server_->removeSession(uuid_);
        return;
    }

    assert(send_que_.front()->getTotalLen() == bytes_transferred);

    std::lock_guard<std::mutex> lock(send_mutex);
    send_que_.pop();
    while (!send_que_.empty()) {
        auto send_node = send_que_.front();
        asio::async_write(
            client_socket_,
            asio::buffer(
                send_node->getData(),
                send_node->getTotalLen()
            ),
            std::bind(
                &Session::handleSend,
                this,
                std::placeholders::_1,
                std::placeholders::_2,
                self
            )
        );
    }
}