#include "http_server.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    HttpServer w;
    w.show();
    return app.exec();
}