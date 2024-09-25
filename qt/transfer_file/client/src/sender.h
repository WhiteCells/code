#ifndef _SENDER_H_
#define _SENDER_H_

#include <QObject>

class Sender : QObject
{
public:
    explicit Sender(QWidget *parent = nullptr);
    ~Sender();

private:
private slots:
    void slot_send_file();
};

#endif // _SENDER_H_