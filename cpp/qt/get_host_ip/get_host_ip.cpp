#include <QCoreApplication>
#include <QNetworkInterface>
#include <QList>
#include <QHostAddress>
#include <QDebug>

bool isInLocalNetwork(const QHostAddress &address)
{
    // Check if the IP address is in private address ranges
    if (address.toString().startsWith("192.168.") ||
        address.toString().startsWith("10.") ||
        (address.toString().startsWith("172.") &&
         (address.toIPv4Address() & 0xF0) == 0x10)) // 172.16.0.0 - 172.31.255.255
    {
        return true;
    }
    return false;
}

bool hasWirelessInterface()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &interface : interfaces) {
        if (interface.type() == QNetworkInterface::Wifi) {
            return true;
        }
    }
    return false;
}

QString getLocalIPAddress()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : list) {
        // 检查是否为 IPv4 地址，且不是回环地址（127.0.0.1）
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
            return address.toString();
        }
    }
    return QString();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 获取所有网络接口
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    // 遍历每个接口
    for (const QNetworkInterface &interface : interfaces) {
        // // 获取该接口的所有 IP 地址
        // // 遍历每个 IP 地址
        // QList<QNetworkAddressEntry> entries = interface.addressEntries();
        // for (const QNetworkAddressEntry &entry : entries) {
        //     QHostAddress ip = entry.ip();
        //     if (ip.protocol() == QAbstractSocket::IPv4Protocol && !ip.isLoopback()) {
        //         // 只打印非回环的 IPv4 地址
        //         qDebug() << "Interface:" << interface.humanReadableName() << "IP Address:" << ip.toString();
        //     }
        // }

        // 只筛选有线和无线的接口
        // QString interfaceName = interface.humanReadableName();
        // wlan wlo1
        // if (interfaceName.startsWith("eth") || interfaceName.startsWith("wlan")) {
        //     // 获取该接口的所有 IP 地址
        //     QList<QNetworkAddressEntry> entries = interface.addressEntries();
        //     for (const QNetworkAddressEntry &entry : entries) {
        //         QHostAddress ip = entry.ip();
        //         if (ip.protocol() == QAbstractSocket::IPv4Protocol && !ip.isLoopback()) {
        //             qDebug() << "Interface:" << interfaceName << "IP Address:" << ip.toString();
        //         }
        //     }
        // }

        // 通过接口类型筛选出有线和无线网络
        // 获取该接口的所有 IP 地址
        QNetworkInterface::InterfaceType type = interface.type();
        if (type == QNetworkInterface::Ethernet || type == QNetworkInterface::Wifi) {
            QList<QNetworkAddressEntry> entries = interface.addressEntries();
            for (const QNetworkAddressEntry &entry : entries) {
                QHostAddress ip = entry.ip();
                if (ip.protocol() == QAbstractSocket::IPv4Protocol && !ip.isLoopback()) {
                    qDebug() << "Interface:" << interface.humanReadableName() << "IP Address:" << ip.toString();
                    qDebug() << isInLocalNetwork(QHostAddress(ip.toString()));
                }
            }
        }
    }
    qDebug() << hasWirelessInterface();

    qDebug() << getLocalIPAddress();
    return a.exec();
}