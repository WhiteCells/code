#ifndef _CENTRAL_STACKED_WIDGET_H_
#define _CENTRAL_STACKED_WIDGET_H_

#include <QStackedWidget>

// 包含 chat_list_widget
// friend_list_widget

class ChatListWidget;
class FriendListWidget;

class CentralStackedWidget : public QStackedWidget
{
public:
    explicit CentralStackedWidget(QWidget *parent = nullptr);
    ~CentralStackedWidget();

private:
    ChatListWidget *chat_list_widget_;     // index 0
    FriendListWidget *friend_list_widget_; // index 1
};

#endif // _CENTRAL_STACKED_WIDGET_H_