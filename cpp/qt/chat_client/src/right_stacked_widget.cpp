#include "right_stacked_widget.h"
#include "widget/chat_splitter.h"
#include "widget/user_info_widget.h"
#include "widget/empty_page_widget.h"

#include <QHBoxLayout>

RightStackedWidget::RightStackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    chat_splitter_(new ChatSplitter()),
    user_info_widget_(new UserInfoWidget()),
    empty_page_widget_(new EmptyPageWidget())
{
    this->addWidget(chat_splitter_);
    this->addWidget(user_info_widget_);
    this->addWidget(empty_page_widget_);
    this->setCurrentIndex(0);
}

RightStackedWidget::~RightStackedWidget()
{
}