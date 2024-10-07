#include "window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
    QSplitter *sub_splitter = new QSplitter(Qt::Vertical);

    QWidget *sub_widget1 = new QWidget();
    QTextEdit *edit1 = new QTextEdit("sub widget1");
    QVBoxLayout *vlayout1 = new QVBoxLayout(sub_widget1);
    vlayout1->addWidget(edit1);
    sub_splitter->addWidget(sub_widget1);

    QWidget *sub_widget2 = new QWidget();
    QTextEdit *edit2 = new QTextEdit("sub widget2");
    QHBoxLayout *hlayout2 = new QHBoxLayout(sub_widget2);
    hlayout2->addWidget(edit2);
    sub_splitter->addWidget(sub_widget2);

    QSplitter *main_splitter = new QSplitter(Qt::Orientation::Horizontal);
    main_splitter->addWidget(new QTextEdit("side widget"));
    main_splitter->addWidget(sub_splitter);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(main_splitter);

    QWidget *main_widget = new QWidget();
    main_widget->setLayout(layout);
    this->setCentralWidget(main_widget);
    this->resize(800, 600);
}

Window::~Window()
{
}