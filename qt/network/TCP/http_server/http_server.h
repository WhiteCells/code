#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_

#include <QWidget>

class QTcpSocket;
class QTcpServer;
class QTextEdit;

class HttpServer : public QWidget {
    Q_OBJECT

public:
    explicit HttpServer(QWidget *parent = nullptr);
    ~HttpServer();

private:
    QTcpServer *tcp_server_;
    QTextEdit *text_edit_;

private slots:
    void slot_handle_connection();
    void slot_handle_data(QTcpSocket *socket);
};

#endif // _HTTP_SERVER_H_