#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QUdpSocket;
class QListWidget;

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private:
    QUdpSocket *socket_;
    QListWidget *log_list_widget_;

private slots:
    void slot_process_datagram(); // 处理接收到的UDP数据包
};

#endif // WIDGET_H