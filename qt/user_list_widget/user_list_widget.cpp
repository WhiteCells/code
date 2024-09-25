#include "user_list_widget.h"
#include <QEvent>
#include <QWheelEvent>
#include <QScrollBar>

UserListWidget::UserListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);
    this->addItem("test1");
    this->addItem("test2");
    this->addItem("test3");
    this->addItem("test3");
    this->addItem("test3");
    this->addItem("test3");
    this->addItem("test3");
    this->addItem("test3");
    this->addItem("test3");
    this->addItem("test3");
    this->addItem("test3");
    // this->addItem(new QListWidgetItem("test1"));
    // this->addItem(new QListWidgetItem("test2"));
    // this->addItem(new QListWidgetItem("test3"));
}

UserListWidget::~UserListWidget()
{
}

bool UserListWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this->viewport()) {
        // 鼠标进入事件
        if (event->type() == QEvent::Enter) {
            static int i = 0;
            qDebug() << "mouse enter" << i++;
            this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        }
        // 鼠标离开事件
        else if (event->type() == QEvent::Leave) {
            static int i = 0;
            qDebug() << "mouse leave" << i++;
            this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        }
    }

    // 鼠标滚动事件
    if (watched == this->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheel_event = static_cast<QWheelEvent *>(event);
        int degree = wheel_event->angleDelta().y() / 8;
        int step = degree / 15; // 滚轮步数
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - step);
        QScrollBar *scroll_bar = this->verticalScrollBar();
        int max_scroll_value = scroll_bar->maximum();
        int current_value = scroll_bar->value();
        if (max_scroll_value - current_value <= 0) {
            static int i = 0;
            qDebug() << "load user: " << i++;
            // emit
        }
    }
    return QListWidget::eventFilter(watched, event);
}
