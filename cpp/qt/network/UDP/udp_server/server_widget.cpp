#include "server_widget.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QListWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkProxy>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , socket_(new QUdpSocket(this))
    , log_list_widget_(new QListWidget()) {

    this->setWindowTitle("udp server");
    this->setMinimumSize(500, 350);

    socket_->setProxy(QNetworkProxy::NoProxy);
    quint16 server_port = 10101;
    bool success = socket_->bind(QHostAddress::Any, server_port);
    if (!success) {
        QMessageBox::critical(this, "Server Start Error", socket_->errorString());
    }
    this->connect(socket_, &QUdpSocket::readyRead, this, &ServerWidget::slot_process_datagram);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    log_list_widget_ = new QListWidget();
    main_layout->addWidget(log_list_widget_);
}

ServerWidget::~ServerWidget() {
}

void ServerWidget::slot_process_datagram() {
    while (socket_->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket_->receiveDatagram();
        QString data_str = QString::fromUtf8(datagram.data());
        log_list_widget_->addItem("Received: " + data_str);
    }
}