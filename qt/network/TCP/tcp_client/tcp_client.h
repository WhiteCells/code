#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <QWidget>

class QTcpSocket;
class QListWidget;
class QPushButton;
class QLineEdit;

class TcpClient : public QWidget {
    Q_OBJECT
public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();

private:
    QTcpSocket  *socket_;
    QListWidget *log_list_widget_;
    QLineEdit   *message_line_edit_;
    QPushButton *send_btn_;

private slots:
    void slot_send_btn_clicked();
};

#endif // _TCP_CLIENT_H_