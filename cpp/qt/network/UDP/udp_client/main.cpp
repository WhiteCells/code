#include "client_widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWidget w;
    w.show();
    return a.exec();
}
