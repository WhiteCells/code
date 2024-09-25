#ifndef FILECLIENT_H
#define FILECLIENT_H

#include <QTcpSocket>
#include <QFile>

class FileClient : public QObject
{
    Q_OBJECT

public:
    explicit FileClient(QObject *parent = nullptr);
    void sendFile(const QString &filePath);

private slots:
    void onConnected();
    void onBytesWritten(qint64 bytes);

private:
    QTcpSocket *socket;
    QFile file;
    QByteArray fileData;
    qint64 bytesSent;
};

#endif // FILECLIENT_H