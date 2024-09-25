#include "widget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFile file(":/qss/splitter");
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "qss file not found";
    }
    else {
        QString qss_str = QLatin1StringView(file.readAll());
        app.setStyleSheet(qss_str);
        file.close();
    }

    Widget w;
    w.show();
    return app.exec();
}