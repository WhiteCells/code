#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    this->setMinimumSize(300, 500);
    this->setMaximumSize(300, 500);

    login_dialog_ = new LoginDialog(this);
    register_dialog_ = new RegisterDialog(this);

    login_dialog_->setWindowFlags(Qt::FramelessWindowHint);
    this->setCentralWidget(login_dialog_);

    this->connect(login_dialog_, &LoginDialog::sig_register_btn_clicked,
                  this, &MainWindow::slot_show_register_dialog);
    this->connect(register_dialog_, &RegisterDialog::sig_cancel_btn_clicked,
                  this, &MainWindow::slot_show_login_dialog);
}

MainWindow::~MainWindow() {

}

void MainWindow::slot_show_login_dialog() {
    qDebug() << "slot_show_login_dialog";
    login_dialog_ = new LoginDialog(this);
    login_dialog_->setWindowFlags(Qt::FramelessWindowHint);
    this->setCentralWidget(login_dialog_);
    this->connect(login_dialog_, &LoginDialog::sig_register_btn_clicked,
                  this, &MainWindow::slot_show_register_dialog);
}

void MainWindow::slot_show_register_dialog() {
    qDebug() << "slot_show_register_dialog";
    register_dialog_ = new RegisterDialog(this);
    register_dialog_->setWindowFlags(Qt::FramelessWindowHint);
    this->setCentralWidget(register_dialog_);
    this->connect(register_dialog_, &RegisterDialog::sig_cancel_btn_clicked,
                  this, &MainWindow::slot_show_login_dialog);
}