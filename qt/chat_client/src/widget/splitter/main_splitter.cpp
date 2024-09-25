#include "main_splitter.h"
#include "chat_splitter.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>

MainSplitter::MainSplitter(QWidget *parent) :
    QSplitter(Qt::Orientation::Horizontal, parent),
    list_widget_(new QWidget()),
    chat_splitter_(new ChatSplitter())
{
    list_widget_->setMinimumWidth(100);
    chat_splitter_->setMinimumWidth(200);
    
    this->addWidget(list_widget_);
    this->addWidget(chat_splitter_);

    this->setHandleWidth(0);
    this->setCollapsible(0, false);
    this->setCollapsible(1, false);
}

MainSplitter::~MainSplitter()
{
}