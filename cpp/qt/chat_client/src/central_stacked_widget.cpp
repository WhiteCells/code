#include "central_stacked_widget.h"
#include "widget/chat_list_widget.h"
#include "widget/friend_list_widget.h"

CentralStackedWidget::CentralStackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    chat_list_widget_(new ChatListWidget()),
    friend_list_widget_(new FriendListWidget())
{
    this->addWidget(chat_list_widget_);
    this->addWidget(friend_list_widget_);
    this->setCurrentIndex(0);
}

CentralStackedWidget::~CentralStackedWidget()
{
}
