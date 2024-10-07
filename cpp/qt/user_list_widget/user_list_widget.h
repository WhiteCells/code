#ifndef _USER_LIST_WIDGET_H_
#define _USER_LIST_WIDGET_H_

#include <QListWidget>

class UserListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit UserListWidget(QWidget *parent = nullptr);
    ~UserListWidget();

private:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void sig_loading_user();
};

#endif // _USER_LIST_WIDGET_H_