#include "chat_splitter.h"
#include "chat_box_widget.h"
#include "chat_edit_widget.h"

ChatSplitter::ChatSplitter(QWidget *parent) :
    QSplitter(Qt::Orientation::Vertical, parent),
    chat_box_widget_(new ChatBoxWidget()),
    chat_edit_widget_(new ChatEditWidget())
{
    this->addWidget(chat_box_widget_);
    this->addWidget(chat_edit_widget_);
    this->setCollapsible(0, false);
    this->setCollapsible(1, false);
    this->setHandleWidth(0);
}

ChatSplitter::~ChatSplitter()
{
}