#include "tcp_client.h"
#include <QTcpSocket>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <qobject.h>

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    socket_(new QTcpSocket(this)),
    log_list_widget_(new QListWidget()),
    message_line_edit_(new QLineEdit()),
    send_btn_(new QPushButton("send")) {

    this->setWindowTitle("tcp client");
    this->setMinimumSize(500, 350);

    this->connect(send_btn_, &QPushButton::clicked,
                  this, &TcpClient::slot_send_btn_clicked);

    socket_->connectToHost(QHostAddress("127.0.0.1"), 10101);
    while (!socket_->waitForConnected()) {
        QMessageBox::critical(this, "connect server error",
                              socket_->errorString());
        socket_->connectToHost(QHostAddress("127.0.0.1"), 10101);
    }
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(log_list_widget_);
    QHBoxLayout *send_layout = new QHBoxLayout();
    send_layout->addWidget(message_line_edit_);
    send_layout->addWidget(send_btn_);
    main_layout->addLayout(send_layout);
}

TcpClient::~TcpClient() {
}

void TcpClient::slot_send_btn_clicked() {
    QString message = message_line_edit_->text();
    if (message.isEmpty()) {
        return;
    }
    // for (int i = 0; i < 100; ++i) {
    auto ret = socket_->write(message.toUtf8());
    // }
}
