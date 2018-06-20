#include "ApplicationFunctions.hpp"
#include "WindowsHandler.hpp"


int main(int argc, char *argv[]) {
  QStringList paths = QCoreApplication::libraryPaths();
  for (int i = 0; i < paths.size(); i++) {
    QCoreApplication::removeLibraryPath(paths.at(i)); // clear library paths list
  }
  paths.append(GetRootPath() + "/plugins"); // add new path
  QCoreApplication::setLibraryPaths(paths);

  QApplication app(argc, argv);
  if (SetupApplication()) {
    WindowsHandler wh;
    return app.exec();
  }

  return -1;
}
