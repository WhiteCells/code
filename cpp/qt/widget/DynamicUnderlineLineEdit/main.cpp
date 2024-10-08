#include <QApplication>
#include <QWidget>
#include "DynamicUnderlineLineEdit.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget w;
    w.setStyleSheet("QWidget{background-color: rgb(26, 32, 50);}");

    DynamicUnderlineLineEdit *lineEdit_1 = new DynamicUnderlineLineEdit(&w);
    lineEdit_1->setGeometry(QRect(160, 134, 201, 31));
    lineEdit_1->setTextColor(Qt::white);
    lineEdit_1->setPlaceholderTextColor(QColor(190, 192, 194));
    lineEdit_1->setFont(QFont("微软雅黑"));
    lineEdit_1->setPlaceholderText("输入用户");
    lineEdit_1->setLinePen(QPen(Qt::red, 2));

    DynamicUnderlineLineEdit *lineEdit_2 = new DynamicUnderlineLineEdit(&w);
    lineEdit_2->setGeometry(QRect(160, 190, 201, 31));
    lineEdit_2->setTextColor(Qt::cyan);
    lineEdit_2->setPlaceholderTextColor(QColor(229, 199, 158));
    lineEdit_2->setFont(QFont("微软雅黑"));
    lineEdit_2->setPlaceholderText("输入密码");
    lineEdit_2->setLinePen(QPen(QColor(255, 150, 0), 2), QPen(Qt::lightGray, 2));

    w.show();
    return a.exec();
}
