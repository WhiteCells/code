#include "mainwindow.h"

#include <QFile>
#include <QString>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/QSS/resource/qss/button.qss");
    file.open(QFile::ReadOnly);
    QString str = file.readAll();
    file.close();

    a.setStyleSheet(str);

    qDebug() << "test";

    MainWindow w;
    w.show();
    return a.exec();
}
