#include "server.h"
#include <QDebug>

FileServer::FileServer(QObject *parent) :
    QTcpServer(parent),
    socket(nullptr)
{
}

void FileServer::startServer()
{
    if (!this->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Could not start server";
    } else {
        qDebug() << "Server started!";
    }
}

void FileServer::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &FileServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &FileServer::onDisconnected);

    qDebug() << "Client connected with descriptor:" << socketDescriptor;
}

void FileServer::onReadyRead()
{
    QByteArray fileData = socket->readAll();  // 读取所有数据
    qDebug() << "Receiving data";

    // 发送数据时见一起文件名发送
    // 打开一个文件用于写入
    file.setFileName("wall.png");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file to write";
        return;
    }

    file.write(fileData);
    file.close();
}

void FileServer::onDisconnected()
{
    qDebug() << "Client disconnected";
    socket->deleteLater();
}