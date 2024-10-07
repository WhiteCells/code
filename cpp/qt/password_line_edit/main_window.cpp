#include "main_window.h"
#include "password_line_edit.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pass_line_edit_(new PasswordLineEdit())
{
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
    QVBoxLayout *line_edit_layout = new QVBoxLayout();
    pass_line_edit_->setPlaceholderText("输入用户");
    line_edit_layout->addWidget(pass_line_edit_);
    QLineEdit *line_edit = new QLineEdit();
    line_edit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    line_edit_layout->addWidget(line_edit);
    main_layout->addLayout(line_edit_layout);
    main_layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding));
    QWidget *main_widget = new QWidget();
    main_widget->setLayout(main_layout);
    this->setCentralWidget(main_widget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (pass_line_edit_->hasFocus() && !pass_line_edit_->geometry().contains(event->pos())) {
        pass_line_edit_->clearFocus();
    }
}
