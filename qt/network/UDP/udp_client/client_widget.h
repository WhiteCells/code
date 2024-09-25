#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>

class QUdpSocket;
class QListWidget;
class QLineEdit;
class QPushButton;

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private:
    QUdpSocket *socket_;
    QListWidget *log_list_widget_;
    QLineEdit *message_line_edit_;
    QPushButton *send_btn_;

private slots:
    void slot_send_datagram(); // 发送数据包的槽函数
};

#endif // CLIENTWIDGET_H