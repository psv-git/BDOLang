#include "./src/Qt/windowshandler.hpp"


int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  WindowsHandler wh;

  return app.exec();
}
