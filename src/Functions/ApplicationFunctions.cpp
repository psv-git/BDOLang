#include "ApplicationFunctions.hpp"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>


QDir rootPath(QDir::currentPath());
QFile configFile(rootPath.absoluteFilePath(DEFAULT_SETTINGS.configFileName));

// add i/o operators for allow QDataStream read/write enum ====================

QDataStream& operator >> (QDataStream& is, LANG& e) {
  is >> (quint32&)e;
  return is;
}

QDataStream& operator << (QDataStream& os, LANG e) {
  os << (quint32)e;
  return os;
}

// application setup ==========================================================

bool SetupApplication() {
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
  if (!configFile.isOpen()) configFile.close();
  if (!configFile.open(QIODevice::ReadOnly)) return;
  QDataStream is(&configFile);
  Settings tmp;
  is >> tmp.language;
  is >> tmp.dataPath;
  is >> tmp.sourceFileName;
  is >> tmp.targetFileName;
  is >> tmp.configFileName;
  is >> tmp.dataDirectoryName;
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
  os << settings.configFileName;
  os << settings.dataDirectoryName;
  configFile.close();
  return true;
}


void SetDefaultSettings() {
  active_settings = DEFAULT_SETTINGS;
}

// ============================================================================

const QString GetDirectoryPath(const QString &title) {
  return QFileDialog::getExistingDirectory(nullptr, title, "/.", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
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
