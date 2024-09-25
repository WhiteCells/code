#include "chat_box_widget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

ChatBoxWidget::ChatBoxWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel("chat box", this);
}

ChatBoxWidget::~ChatBoxWidget()
{
}

void ChatBoxWidget::initUi()
{
    
}