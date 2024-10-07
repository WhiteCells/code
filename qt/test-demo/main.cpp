#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WebBrowser browser;
    browser.resize(1024, 768);
    browser.show();

    return app.exec();
}