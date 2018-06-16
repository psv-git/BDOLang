#include "./src/Qt/windowshandler.hpp"
#include <QApplication>


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  WindowsHandler wh;

  return a.exec();
}
