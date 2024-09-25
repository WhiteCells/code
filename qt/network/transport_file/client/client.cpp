#include "client.h"
#include <QDebug>

FileClient::FileClient(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket(this)),
    bytesSent(0)
{
    connect(socket, &QTcpSocket::connected, this, &FileClient::onConnected);
    connect(socket, &QTcpSocket::bytesWritten, this, &FileClient::onBytesWritten);
}

void FileClient::sendFile(const QString &filePath)
{
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file";
        return;
    }
    fileData = file.readAll();
    file.close();

    // 发送的时候才连接
    socket->connectToHost("127.0.0.1", 12345);
}

void FileClient::onConnected()
{
    qDebug() << "Connected to server";
    bytesSent = socket->write(fileData);  // 发送文件内容
    qDebug() << "Sent" << bytesSent << "bytes";
    QByteArray buffer;
    const qint64 block_size = 64 * 1024;
    while (!file.atEnd()) {
        buffer = file.read(block_size);
        socket->write(buffer);
        socket->waitForBytesWritten();
    }
    file.close();
    socket->disconnectFromHost();
}

void FileClient::onBytesWritten(qint64 bytes)
{
    bytesSent += bytes;
    qDebug() << "Written" << bytes << "bytes in total";
    
    if (bytesSent >= fileData.size()) {
        qDebug() << "File sent completely";
        socket->disconnectFromHost();
    }
}