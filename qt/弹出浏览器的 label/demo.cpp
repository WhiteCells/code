#include <QApplication>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // LinkLabel l("连接: <a href=\"https://www.example.com\">Click here to visit example.com</a>");
    // l.show();

    QLabel label1("link: <a href=\"https://www.baidu.com\">baidu</a>");
    // label1.setTextInteractionFlags(Qt::TextBrowserInteraction);
    label1.setOpenExternalLinks(true);
    label1.show();

    return app.exec();
}

#include "demo.moc"
