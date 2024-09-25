#include "tcp_server.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    tcp_server_(new QTcpServer(this)),
    log_list_widget_(new QListWidget()) {

    this->setWindowTitle("tcp server");
    this->setMinimumSize(500, 350);

    this->connect(tcp_server_, &QTcpServer::newConnection, this,
                  &TcpServer::slot_accept_connection);
    bool success = tcp_server_->listen(QHostAddress::Any, 10101);
    if (!success) {
        QMessageBox::critical(this, "server start error",
                              tcp_server_->errorString());
        exit(1);
    }

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(log_list_widget_);
}

TcpServer::~TcpServer() {
}

void TcpServer::slot_accept_connection() {
    client_socket_          = tcp_server_->nextPendingConnection();
    QString client_ip_str   = client_socket_->peerAddress().toString();
    QString client_port_str = QString::number(client_socket_->peerPort());

    QString log = client_ip_str + ":" + client_port_str;
    log_list_widget_->addItem(log + " online");

    this->connect(client_socket_, &QTcpSocket::readyRead,
                  this, &TcpServer::slot_process_data);
    this->connect(client_socket_, &QTcpSocket::disconnected, this, [this, log]() {
        log_list_widget_->addItem(log + " offline");
        client_socket_->deleteLater();
    });
}

void TcpServer::slot_process_data() {
    QByteArray request_byte_array = client_socket_->readAll();
    // process
    QString request_str(request_byte_array);
    log_list_widget_->addItem(request_str);

    QString response_str = request_str;
    client_socket_->write(response_str.toUtf8());
}