#include "widget.h"
#include "main_splitter.h"
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    main_splitter_(new MainSplitter())
{
    QHBoxLayout *main_hlayout = new QHBoxLayout();
    main_hlayout->addWidget(main_splitter_);
    main_hlayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(main_hlayout);
}

Widget::~Widget()
{
}