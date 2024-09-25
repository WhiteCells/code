#include "main_splitter.h"
#include "central_stacked_widget.h"
#include "right_stacked_widget.h"

MainSplitter::MainSplitter(QWidget *parent) :
    QSplitter(Qt::Orientation::Horizontal, parent),
    central_stacked_widget_(new CentralStackedWidget()),
    right_stacked_widget_(new RightStackedWidget())
{
    central_stacked_widget_->setMinimumWidth(100);
    right_stacked_widget_->setMinimumWidth(100);
    // right_stacked_widget_->setMaximumWidth(300);
    this->addWidget(central_stacked_widget_);
    this->addWidget(right_stacked_widget_);
    this->setCollapsible(0, false);
    this->setCollapsible(1, false);
    this->setHandleWidth(0);
}

MainSplitter::~MainSplitter()
{
}