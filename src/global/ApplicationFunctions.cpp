#include "ApplicationFunctions.hpp"


QFontDatabase *fontsList;

// service ====================================================================

const QString GetDirectoryPath(const QString &title) {
  return QFileDialog::getExistingDirectory(nullptr, title, "/.", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}


QString GetRootPath() {
  return QDir::currentPath();
}


QFont GetFont(const QString &family, const QString &style, int pointSize) {
  return fontsList->font(family, style, pointSize);
}

// files ======================================================================

// extStr may be "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)" for example
const QString GetFilePath(const QString &title, const QString &extStr) {
  return QFileDialog::getOpenFileName(nullptr, title, "./", extStr);
}


const QString GetFileName(const QString &title, const QString &extStr) {
  QString filePath = GetFilePath(title, extStr);
  QFileInfo fileInfo(filePath);
  return fileInfo.fileName();
}


void OpenFile(QFile& file, QFlags<QIODevice::OpenModeFlag> openMode, const QString &functionName) {
  if (!file.open(openMode)) {
    ErrorHandler::getInstance().addException("In function \"" + functionName + "\" opening \"" + file.fileName() + "\" file was failed.");
    throw false;
  }
}


void CloseFile(QFile& file, const QString &functionName) {
  file.close();
  if (file.isOpen()) {
    ErrorHandler::getInstance().addException("In function \"" + functionName + "\" closing \"" + file.fileName() + "\" file was failed.");
    throw false;
  }
}


void RemoveFile(QFile& file, const QString &functionName) {
  if (file.isOpen()) CloseFile(file, functionName);
  if (!file.remove()) {
    ErrorHandler::getInstance().addException("In function \"" + functionName + "\" removing \"" + file.fileName() + "\" file was failed.");
    throw false;
  }
}

// application setup ==========================================================

bool SetupApplication() {
  // setup dependency plugins
  QStringList paths = QCoreApplication::libraryPaths();
  for (int i = 0; i < paths.size(); i++) {
    QCoreApplication::removeLibraryPath(paths.at(i)); // clear library paths list
  }
  paths.append(GetRootPath() + "/plugins"); // add new path
  QCoreApplication::setLibraryPaths(paths);

  // read settings from config file
  Settings::getInstance().getSetting("language/language");
  Settings::getInstance().getSetting("compressing/compressing_level");
  Settings::getInstance().getSetting("path/data_path");
  Settings::getInstance().getSetting("path/source_name");
  Settings::getInstance().getSetting("path/target_name");
  Settings::getInstance().getSetting("path/text_name");

  // create data directory if not exist
  QDir rootPath(GetRootPath());
  if (!rootPath.exists(DEFAULT_SETTINGS.dataDirectoryName)) {
   if (!rootPath.mkdir(DEFAULT_SETTINGS.dataDirectoryName)) return false;
  }

  return true;
}


void SetFonts(QFontDatabase &fontsDataBase) {
  fontsList = &fontsDataBase;
  // set fonts
  fontsList->addApplicationFont(":/fonts/liberation-fonts-ttf/LiberationMono-Bold.ttf");
  fontsList->addApplicationFont(":/fonts/liberation-fonts-ttf/LiberationMono-Regular.ttf");
  fontsList->addApplicationFont(":/fonts/liberation-fonts-ttf/LiberationSans-Bold.ttf");
  fontsList->addApplicationFont(":/fonts/liberation-fonts-ttf/LiberationSans-Regular.ttf");
  fontsList->addApplicationFont(":/fonts/liberation-fonts-ttf/LiberationSerif-Bold.ttf");
  fontsList->addApplicationFont(":/fonts/liberation-fonts-ttf/LiberationSerif-Regular.ttf");
}
