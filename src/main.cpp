#include "GlobalClasses.hpp"
#include "WindowsHandler.hpp"


int RunApplication(int argc, char *argv[]) {
  // setup dependency plugins
  QStringList paths = QCoreApplication::libraryPaths();
  for (int i = 0; i < paths.size(); i++) {
    QCoreApplication::removeLibraryPath(paths.at(i)); // clear library paths list
  }
  paths.append(GetRootPath() + "/plugins"); // add new path
  QCoreApplication::setLibraryPaths(paths);

  // create data directory if not exist
  QDir rootPath(GetRootPath());
  if (!rootPath.exists(DEFAULT_SETTINGS.dataDirectoryName)) {
    rootPath.mkdir(DEFAULT_SETTINGS.dataDirectoryName);
  }

  QApplication app(argc, argv);

  SettingsHandler::getInstance().setFonts();
  WindowsHandler wh;

  return app.exec();
}


int main(int argc, char *argv[]) {
  return RunApplication(argc, argv);
}
