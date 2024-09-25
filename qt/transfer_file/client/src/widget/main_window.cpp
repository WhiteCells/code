#include "main_window.h"
#include "widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    widget_(new Widget())
{
    this->setCentralWidget(widget_);
}

MainWindow::~MainWindow()
{
}
