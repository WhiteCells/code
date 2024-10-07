#ifndef _ACCOUNT_LABEL_H_
#define _ACCOUNT_LABEL_H_

#include <QLabel>

class AccountLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AccountLabel(const QString text, QWidget *parent = nullptr);
    ~AccountLabel();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sig_clicked(const QString &account_str);
};

#endif // _ACCOUNT_LABEL_H_