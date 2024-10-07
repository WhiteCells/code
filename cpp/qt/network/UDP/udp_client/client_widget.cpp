#include "client_widget.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkProxy>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    socket_(new QUdpSocket()),
    log_list_widget_(new QListWidget()),
    message_line_edit_(new QLineEdit()),
    send_btn_(new QPushButton("send")) {

    this->setWindowTitle("udp client");
    this->setMinimumSize(500, 350);

    socket_->setProxy(QNetworkProxy::NoProxy);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(log_list_widget_);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(message_line_edit_);
    hlayout->addWidget(send_btn_);
    main_layout->addLayout(hlayout);

    this->connect(send_btn_, &QPushButton::clicked, this, &ClientWidget::slot_send_datagram);
}

ClientWidget::~ClientWidget() {
}

void ClientWidget::slot_send_datagram() {
    QString message = message_line_edit_->text();
    if (message.isEmpty()) {
        return;
    }

    QHostAddress server_ip {"127.0.0.1"};
    quint16 server_port = 10101;

    qint64 bytes_sent = socket_->writeDatagram(message.toUtf8(), server_ip, server_port);
    if (bytes_sent == -1) {
        log_list_widget_->addItem("Failed to send message: " + socket_->errorString());
    } else {
        log_list_widget_->addItem("Sent: " + message);
    }
}