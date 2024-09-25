#ifndef _FRIEND_LIST_WIDGET_H_
#define _FRIEND_LIST_WIDGET_H_

#include <QListWidget>

class FriendListWidget : public QListWidget
{
public:
    explicit FriendListWidget(QWidget *parent = nullptr);
    ~FriendListWidget();

protected:
private:
};

#endif // _FRIEND_LIST_WIDGET_H_