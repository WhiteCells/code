#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class FileClient : public QObject
{
    Q_OBJECT

public:
    FileClient(QObject *parent = nullptr) :
        QObject(parent)
    {
        socket = new QTcpSocket(this);
        connect(socket, &QTcpSocket::connected, this, &FileClient::onConnected);
        connect(socket, &QTcpSocket::bytesWritten, this, &FileClient::onBytesWritten);
        connect(socket, &QTcpSocket::disconnected, this, &FileClient::onDisconnected);
    }

    void connectServer(const QString &host, qint16 port)
    {
        if (socket->state() != QAbstractSocket::UnconnectedState) {
            qWarning() << "Socket is already connected or in connecting state.";
            return;
        }
        socket->connectToHost(host, port);
    }

    void sendFile(QString file_path)
    {
        file.setFileName(file_path);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "failed to open file: " << file.fileName();
            return;
        }

        if (!socket->isOpen()) {
            qWarning() << "socket is not open";
            return;
        }

        QDataStream out(socket);
        out << file_path;
        QByteArray file_data = file.readAll();
        socket->write(file_data);
        socket->flush();
        file.close();
    }

private slots:
    void onConnected()
    {
        qDebug() << "conneted to server";
    }

    void onBytesWritten(qint64 bytes)
    {
        qDebug() << bytes << " bytes written";
    }

    void onDisconnected()
    {
        qDebug() << "disconneted to server";
    }

private:
    QTcpSocket *socket;
    QFile file;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileClient client;
    client.connectServer("127.0.0.1", 11451);
    client.sendFile("./file.txt");
    return a.exec();
}

#include "client.moc"