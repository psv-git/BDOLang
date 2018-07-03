#include <QFileDialog>
#include <QFileInfo>
#include "ApplicationFunctions.hpp"
#include "WindowsHandler.hpp"


// service ====================================================================

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


void Delay(int ms) {
  QEventLoop loop;
  QTimer::singleShot(ms, &loop, &QEventLoop::quit);
  loop.exec();
}

// paths & files ======================================================================

const QString GetDirectoryPath(const QString &title) {
  return QFileDialog::getExistingDirectory(nullptr, title, "/.", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}


QString GetRootPath() {
  return QDir::currentPath();
}


// extStr may be "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)" for example
const QString GetFilePath(const QString &title, const QString &extStr) {
  return QFileDialog::getOpenFileName(nullptr, title, "./", extStr);
}


const QString GetFileName(const QString &title, const QString &extStr) {
  QString filePath = GetFilePath(title, extStr);
  QFileInfo fileInfo(filePath);
  return fileInfo.fileName();
}


void OpenFile(QFile& file, QFlags<QIODevice::OpenModeFlag> openMode) {
  if (!file.open(openMode)) throw std::ios_base::failure("opening \"" + file.fileName().toStdString() + "\" file was failed.");
}


void CloseFile(QFile& file) {
  file.close();
  if (file.isOpen()) throw std::ios_base::failure("closing \"" + file.fileName().toStdString() + "\" file was failed.");
}


void RemoveFile(QFile& file) {
  if (file.isOpen()) file.close();;
  if (!file.remove()) throw std::ios_base::failure("removing \"" + file.fileName().toStdString() + "\" file was failed.");
}
