#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <QTcpSocket>
#include <QFile>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private:
    QTcpSocket *socket_;
    QFile file_;

public slots:
    void slot_send_file(const QString &file_path);
    void slot_connect_host(const QHostAddress &address, qint16 port);

private slots:
    void slot_connected();
    void slot_disconnected();
    void slot_bytes_writen(qint64 bytes);
    void slot_occurred_error(QAbstractSocket::SocketError socket_error);
};

#endif // _CLIENT_H_