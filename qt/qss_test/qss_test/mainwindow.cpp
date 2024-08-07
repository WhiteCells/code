#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    btn1 = new QPushButton(this);
    btn2 = new QPushButton(this);

    // QString qss = "QPushButton{ color: blue; font: 20px }";

    btn2->move(100, 100);

    btn1->setText("btn1");
    btn2->setText("btn2");

    // btn1->setStyleSheet(qss);
    // btn2->setStyleSheet(qss);

    this->connect(ui->pushButton, &QPushButton::clicked,
                     this, &::MainWindow::on_pushButton_pressed);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    qDebug("btn pressed");
    this->setWindowTitle("tilte changed");
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug("btn clicked");
}

