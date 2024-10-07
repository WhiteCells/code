#include <QApplication>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QDebug>

// TLV
// +-----------+-----------+-----------+
// | file_name | file_size | file_data |
// +-----------+-----------+-----------+

// todo
// 1. 图形化界面
//      1. 选择文件的窗口
//

class FileClient : public QObject
{
    Q_OBJECT

public:
    FileClient(QObject *parent = nullptr) :
        QObject(parent), socket(new QTcpSocket(this))
    {
        this->connect(socket, &QTcpSocket::connected, this, &FileClient::onConnected);
        this->connect(socket, &QTcpSocket::bytesWritten, this, &FileClient::onBytesWritten);
        this->connect(socket, &QTcpSocket::disconnected, this, &FileClient::onDisconnected);
        // this->connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), this, &FileClient::onErrorOccurred);
        this->connect(socket, &QTcpSocket::errorOccurred, this, &FileClient::onErrorOccurred);
    }

    void connectServer(const QString &host, qint16 port)
    {
        if (socket->state() != QAbstractSocket::UnconnectedState) {
            qWarning() << "Socket is already connected or in connecting state.";
            return;
        }
        socket->connectToHost(host, port);
    }

    void setFilePath(QString file_path)
    {
        file.setFileName(file_path);
    }

private slots:
    void onConnected()
    {
        qDebug() << "conneted to server";
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "failed to open file: " << file.fileName();
            return;
        }

        QDataStream out(socket);
        out << file.fileName();
        QByteArray file_data = file.readAll();
        out << file_data.size();
        socket->write(file_data);
        socket->flush();
        file.close();
    }

    void onBytesWritten(qint64 bytes)
    {
        qDebug() << bytes << "bytes written";
    }

    void onDisconnected()
    {
        qDebug() << "disconneted to server";
    }

    void onErrorOccurred(QTcpSocket::SocketError socket_error)
    {
        qDebug() << "error: " << socket->errorString();
        switch (socket_error) {
            case QTcpSocket::ConnectionRefusedError:
                qDebug("connection refused");
                break;
            case QTcpSocket::RemoteHostClosedError:
                qDebug("remote host closed connection");
                break;
            case QTcpSocket::HostNotFoundError:
                qDebug("host not found");
                break;
            case QTcpSocket::SocketTimeoutError:
                qDebug("connection timeout");
                break;
            case QTcpSocket::NetworkError:
                qDebug("network error");
                break;
            default:
                qDebug("other error");
                break;
        }
    }

private:
    QTcpSocket *socket;
    QFile file;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileClient client;
    client.setFilePath("../testfile/send/faf.zip");
    client.connectServer("127.0.0.1", 11451);
    return a.exec();
}

#include "client.moc"