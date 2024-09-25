#include "chat_splitter.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QHBoxLayout>

ChatSplitter::ChatSplitter(QWidget *parent) :
    QSplitter(Qt::Orientation::Vertical, parent),
    widget1_(new QWidget()),
    widget2_(new QWidget())
{
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    QTextEdit *text_edit1 = new QTextEdit("edit1");
    hlayout1->addWidget(text_edit1);
    hlayout1->setContentsMargins(0, 0, 0, 0);
    widget1_->setLayout(hlayout1);

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    QTextEdit *text_edit2 = new QTextEdit("edit1");
    hlayout2->addWidget(text_edit2);
    hlayout2->setContentsMargins(0, 0, 0, 0);
    widget2_->setLayout(hlayout2);

    this->addWidget(widget1_);
    this->addWidget(widget2_);

    this->setHandleWidth(1);
    this->setCollapsible(0, false);
    this->setCollapsible(1, false);
}

ChatSplitter::~ChatSplitter()
{
}