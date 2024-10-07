#include "http_client.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    HttpClient w;
    w.show();
    return app.exec();
}