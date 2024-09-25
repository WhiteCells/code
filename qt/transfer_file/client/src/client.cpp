#include "client.h"
#include <QDebug>

Client::Client(QWidget *parent) :
    socket_(new QTcpSocket(this))
{
    this->connect(socket_, &QTcpSocket::connected, this, &Client::slot_connected);
    this->connect(socket_, &QTcpSocket::disconnected, this, &Client::slot_disconnected);
    this->connect(socket_, &QTcpSocket::bytesWritten, this, &Client::slot_bytes_writen);
    this->connect(socket_, &QTcpSocket::errorOccurred, this, &Client::slot_occurred_error);
}

Client::~Client()
{
}

void Client::slot_connected()
{
    qDebug() << "connected";
}

void Client::slot_disconnected()
{
    qDebug() << "disconnected";
}

void Client::slot_bytes_writen(qint64 bytes)
{
    qDebug() << "writen bytes: " << bytes;
}

void Client::slot_occurred_error(QAbstractSocket::SocketError socket_error)
{
    // qDebug() << "occurred error: " << socket_->errorString();
    switch (socket_error) {
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "connect refused";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            qDebug() << "remote host closed";
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug() << "host not found";
            break;
        case QAbstractSocket::SocketTimeoutError:
            qDebug() << "socket time out";
            break;
        case QAbstractSocket::NetworkError:
            qDebug() << "network error";
            break;
        default:
            qDebug() << "unknown error";
            break;
    }
}

void Client::slot_connect_host(const QHostAddress &address, qint16 port)
{
    qDebug() << "ip: " << address.toString();
    qDebug() << "port: " << port;
    socket_->connectToHost(address, port);
}

void Client::slot_send_file(const QString &file_path)
{
    file_.setFileName(file_path);
    if (!file_.open(QFile::ReadOnly)) {
        qDebug() << "failed to open file";
        return;
    }

    QDataStream out(socket_);
    // 转为字节流
    QByteArray file_data = file_.readAll();
    // tlv
    out << file_.fileName() << file_data.size();
    socket_->write(file_data);
    socket_->flush();
    file_.close();
}
