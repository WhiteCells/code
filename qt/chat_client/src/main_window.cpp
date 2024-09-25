#include "main_window.h"
#include "left_side_widget.h"
#include "widget/main_splitter.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    main_widget_(new QWidget()),
    main_hlayout_(new QHBoxLayout()),
    left_side_widget_(new LeftSideWidget()),
    main_splitter_(new MainSplitter())
{
    left_side_widget_->setFixedWidth(50);
    main_hlayout_->addWidget(left_side_widget_);
    main_hlayout_->addWidget(main_splitter_);
    main_widget_->setLayout(main_hlayout_);
    main_widget_->setContentsMargins(0, 0, 0, 0);
    this->setCentralWidget(main_widget_);
}

MainWindow::~MainWindow()
{
}
