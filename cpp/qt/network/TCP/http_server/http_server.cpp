#include "http_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>

HttpServer::HttpServer(QWidget *parent) :
    QWidget(parent),
    tcp_server_(new QTcpServer(this)),
    text_edit_(new QTextEdit()) {

    this->setWindowTitle("http server");
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(text_edit_);

    if (!tcp_server_->listen(QHostAddress("127.0.0.1"), 10101)) {
        qDebug() << "listen failed";
        return;
    }

    this->connect(tcp_server_, &QTcpServer::newConnection,
                  this, &HttpServer::slot_handle_connection);
}

HttpServer::~HttpServer() {
}

void HttpServer::slot_handle_connection() {
    QTcpSocket *socket = tcp_server_->nextPendingConnection();
    this->connect(socket, &QTcpSocket::readyRead,
                  this, std::bind(&HttpServer::slot_handle_data, this, socket));
    this->connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

void HttpServer::slot_handle_data(QTcpSocket *socket) {
    auto data = socket->readAll();
    auto json_error = QJsonParseError();
    auto doc = QJsonDocument::fromJson(data, &json_error);
    if (json_error.error != QJsonParseError::NoError) {
        qDebug() << "failed to parse JSON: " << json_error.errorString();
        return;
    }
    auto root = doc.object();
    auto user = root["user"].toString();
    auto contect = root["contact"].toString();

    auto ret_root = QJsonObject();
    ret_root["id"] = "111111";
    auto ret_doc = QJsonDocument(ret_root);
    auto response_data = ret_doc.toJson(QJsonDocument::Compact);
    QByteArray response_http = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";
    response_http.append(response_data);
    socket->write(response_http);
    socket->flush();
    socket->disconnectFromHost();
}