#include "chat_edit_widget.h"
#include <QLabel>

ChatEditWidget::ChatEditWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel("chat edit", this);
}
ChatEditWidget::~ChatEditWidget()
{
}