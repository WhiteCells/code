#include "client.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FileClient client;
    client.sendFile("wall.png");
    return app.exec();
}