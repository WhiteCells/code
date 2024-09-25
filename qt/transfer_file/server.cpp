#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class FileServer : public QObject
{
    Q_OBJECT
public:
    FileServer(QObject *parent = nullptr) :
        QObject(parent)
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
    }

    void onReadyRead()
    {
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        QDataStream in(socket);

        if (!file.isOpen()) {
            QString file_name;
            in >> file_name;
            file.setFileName(file_name);
            if (!file.open(QIODevice::WriteOnly)) {
                qWarning() << "failed to open file: " << file_name;
                return;
            }
        }
        QByteArray file_data = socket->readAll();
        file.write(file_data);
    }

    void onDisconnected()
    {
        file.close();
        qDebug() << "File received and saved";
    }

private:
    QTcpServer *server;
    QFile file;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileServer server;
    return a.exec();
}

#include "server.moc"