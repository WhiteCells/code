#ifndef FILESERVER_H
#define FILESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class FileServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit FileServer(QObject *parent = nullptr);
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *socket;
    QFile file;
};

#endif // FILESERVER_H
