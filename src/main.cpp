#include "ApplicationFunctions.hpp"
#include "WindowsHandler.hpp"

#include <iostream>
int main(int argc, char *argv[]) {
  QStringList paths = QCoreApplication::libraryPaths();
  for (int i = 0; i < paths.size(); i++) {
//    std::cerr << paths.at(i).toStdString() << std::endl << std::endl;
    QCoreApplication::removeLibraryPath(paths.at(i));
  }

  paths.append(GetRootPath() + "/plugins");
  QCoreApplication::setLibraryPaths(paths);
//  for (int i = 0; i < paths.size(); i++) {
//    std::cerr << paths.at(i).toStdString() << std::endl;
//  }

  QApplication app(argc, argv);
  if (SetupApplication()) {
    WindowsHandler wh;
    return app.exec();
  }
  return -1;
}
