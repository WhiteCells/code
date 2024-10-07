#include "widget.h"
#include "dynamic_line_edit.h"
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent) {
    DynamicLineEdit *line_edit = new DynamicLineEdit();
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(line_edit);
    this->resize(300, 100);
}

Widget::~Widget() {
}
