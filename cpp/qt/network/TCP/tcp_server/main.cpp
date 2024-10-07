#include "tcp_server.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TcpServer    w;
    w.show();
    return app.exec();
}