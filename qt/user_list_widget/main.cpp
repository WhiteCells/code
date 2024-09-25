#include "user_list_widget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    UserListWidget list_widget;
    list_widget.show();
    return app.exec();
}