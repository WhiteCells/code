#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QDebug>

// todo
// 1. 文件保存目录
//      取传输文件的路径的文件名，保存到指定目录
//      不设置时，使用默认保存路径，即当前可执行文件路径
// 2. 多线程处理文件传输
//      
// 3. 分模块负责
//      1. 管理连接模块
//      2. 管理读写模块
//      3. 管理逻辑模块
//

// 支持所有文件传输格式

class FileServer : public QObject
{
    Q_OBJECT
public:
    FileServer(QObject *parent = nullptr) :
        QObject(parent),
        file_size(0),
        bytes_received(0)
    {
        server = new QTcpServer(this);
        connect(server, &QTcpServer::newConnection, this, &FileServer::onNewConnection);
        if (server->listen(QHostAddress::Any, 11451)) {
            qDebug() << "Server started on port 11451";
        }
        else {
            qDebug() << "Server could not start!";
        }
    }

private slots:
    void onNewConnection()
    {
        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &FileServer::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &FileServer::onDisconnected);
        qDebug() << "Client connected";
    }

    void onReadyRead()
    {
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        QDataStream in(socket);

        // bug
        if (file_name.isEmpty()) {
            if (socket->bytesAvailable() < (int)sizeof(qint64))
                return;

            in >> file_name >> file_size;
            file.setFileName(file_name);

            if (!file.open(QIODevice::WriteOnly)) {
                qWarning() << "Failed to open file:" << file_name;
                return;
            }

            qDebug() << "Receiving file:" << file_name << "with size:" << file_size;
        }

        // Read the file data
        QByteArray file_data = socket->readAll();
        qDebug() << file_data;
        bytes_received += file_data.size();
        file.write(file_data);

        qDebug() << "Bytes received:" << bytes_received << "/" << file_size;

        // Check if the file is fully received
        if (bytes_received >= file_size) {
            file.close();
            qDebug() << "File received and saved";
            socket->disconnectFromHost();
        }
    }

    void onDisconnected()
    {
        file.close();
        qDebug() << "Client disconnected";
    }

private:
    QTcpServer *server;
    QFile file;
    QString file_name;
    qint64 file_size;
    qint64 bytes_received;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileServer server;
    return a.exec();
}

#include "server.moc"