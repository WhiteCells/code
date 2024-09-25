#include "tcp_client.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  TcpClient w;
  w.show();
  return app.exec();
}