#include "server_widget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();
    return a.exec();
}
