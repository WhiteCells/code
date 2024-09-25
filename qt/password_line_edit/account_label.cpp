#include "account_label.h"
#include <QMouseEvent>

AccountLabel::AccountLabel(const QString text, QWidget *parent) :
    QLabel(parent)
{
    this->setText(text);
    this->setAlignment(Qt::AlignCenter);
}

AccountLabel::~AccountLabel()
{
}

void AccountLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit sig_clicked(this->text());
    }
}
