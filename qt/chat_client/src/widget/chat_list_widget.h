#ifndef _CHAT_LIST_WIDGET_H_
#define _CHAT_LIST_WIDGET_H_

#include <QListWidget>

class ChatListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ChatListWidget(QWidget *parent = nullptr);
    ~ChatListWidget();

    void addChatUserLabel();
};

#endif // _CHAT_LIST_WIDGET_H_