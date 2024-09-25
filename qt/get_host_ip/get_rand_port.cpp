#include <QCoreApplication>
#include <QTcpServer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpServer server;

    // 监听随机端口，0 表示由系统自动分配未使用的端口
    if (server.listen(QHostAddress::Any, 0)) {
        quint16 randomPort = server.serverPort();
        qDebug() << "Server is listening on random port:" << randomPort;
    } else {
        qDebug() << "Failed to start server!";
    }

    return a.exec();
}