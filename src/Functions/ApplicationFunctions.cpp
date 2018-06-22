#include "ApplicationFunctions.hpp"


QFile configFile;
QStringList exceptionsMessagesList;

// exceptions =================================================================

void AddException(const QString &exceptionMessage) {
  exceptionsMessagesList.push_back(exceptionMessage);
}


const QString GetExceptionsMessage() {
  QString exceptionMessage;
  for (int i = 0; i < exceptionsMessagesList.size(); i++) {
    exceptionMessage += exceptionsMessagesList.at(i);
    exceptionMessage.push_back('\n');
  }
  exceptionsMessagesList.clear();
  return exceptionMessage;
}

// service ====================================================================

void Delay(int timeToWait) {
  QTime milliseconds = QTime::currentTime().addMSecs(timeToWait);
  while(QTime::currentTime() < milliseconds) {
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
  }
}


const QString GetDirectoryPath(const QString &title) {
  return QFileDialog::getExistingDirectory(nullptr, title, "/.", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}


QString GetRootPath() {
  return QDir::currentPath();
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
    AddException("In function \"" + functionName + "\" opening \"" + file.fileName() + "\" file was failed.");
    throw;
  }
}


void CloseFile(QFile& file, const QString &functionName) {
  file.close();
  if (file.isOpen()) {
    AddException("In function \"" + functionName + "\" closing \"" + file.fileName() + "\" file was failed.");
    throw;
  }
}


void RemoveFile(QFile& file, const QString &functionName) {
  if (file.isOpen()) CloseFile(file, functionName);
  if (!file.remove()) {
    AddException("In function \"" + functionName + "\" removing \"" + file.fileName() + "\" file was failed.");
    throw;
  }
}

// application setup ==========================================================

bool SetupApplication() {
  QDir rootPath(GetRootPath());
  configFile.setFileName(rootPath.absoluteFilePath(DEFAULT_SETTINGS.configFileName));
  if (!rootPath.exists(DEFAULT_SETTINGS.dataDirectoryName)) {
   if (!rootPath.mkdir(DEFAULT_SETTINGS.dataDirectoryName)) return false; // create data directory if not exists
  }
  if (!configFile.exists()) {
    if (!configFile.open(QIODevice::WriteOnly)) return false; // create config file if not exist
    configFile.close();
    WriteConfigFile(active_settings); // active_settings == DEFAULT_SETTINGS on app start always
  } else {
    ReadConfigFile(active_settings); // read settings if config file exist
  }
  return true;
}


void ReadConfigFile(Settings &settings) {
  if (configFile.isOpen()) configFile.close();
  if (!configFile.open(QIODevice::ReadOnly)) return;
  QDataStream is(&configFile);
  Settings tmp;
  is >> tmp.language;
  is >> tmp.dataPath;
  is >> tmp.sourceFileName;
  is >> tmp.targetFileName;

  is << tmp.dataDirectoryName;
  is >> tmp.configFileName;

  settings = tmp;
  configFile.close();
}


bool WriteConfigFile(Settings& settings) {
  if (configFile.isOpen()) configFile.close();
  if (!configFile.open(QIODevice::WriteOnly)) return false;
  QDataStream os(&configFile);
  os << settings.language;
  os << settings.dataPath;
  os << settings.sourceFileName;
  os << settings.targetFileName;

  os << settings.dataDirectoryName;
  os << settings.configFileName;

  configFile.close();
  return true;
}


void SetDefaultSettings() {
  active_settings = DEFAULT_SETTINGS;
}

// i/o ========================================================================

// add i/o operators for allow QDataStream read/write enum LANG
QDataStream& operator >> (QDataStream& is, LANG& e) {
  is >> (quint32&)e;
  return is;
}

QDataStream& operator << (QDataStream& os, LANG e) {
  os << (quint32)e;
  return os;
}
