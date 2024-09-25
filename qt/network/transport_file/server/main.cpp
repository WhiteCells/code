#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileServer server;
    server.startServer(); // 启动服务器
    return a.exec();
}