#include "main_window.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile file(":/qss/widget");
    if (file.open(QFile::ReadOnly)) {
        QString qss_str = QLatin1StringView(file.readAll());
        file.close();
        app.setStyleSheet(qss_str);
    }
    else {
        qDebug() << "qss file not found";
    }

    MainWindow w;
    w.show();
    return app.exec();
}