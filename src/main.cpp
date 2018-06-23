#include "ApplicationFunctions.hpp"
#include "WindowsHandler.hpp"


int main(int argc, char *argv[]) {
  if (SetupApplication()) {
    QApplication app(argc, argv);
    QFontDatabase fontsDataBase;
    SetFonts(fontsDataBase);
    WindowsHandler wh;
    return app.exec();
  }

  return -1;
}
