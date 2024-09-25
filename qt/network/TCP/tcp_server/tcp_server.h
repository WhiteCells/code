#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <QWidget>

class QTcpServer;
class QTcpSocket;
class QListWidget;

class TcpServer : public QWidget {
    Q_OBJECT
public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private:
    QTcpServer  *tcp_server_;
    QTcpSocket  *client_socket_;
    QListWidget *log_list_widget_;

private slots:
    void slot_accept_connection();
    void slot_process_data();
};

#endif // _TCP_SERVER_H_