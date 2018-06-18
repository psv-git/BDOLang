#include "ApplicationFunctions.hpp"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>


bool SetupApplication() {
  if (!SetDataFolder()) return false;

//  QFile configFile(QDir::currentPath());
//  if (!configFile.exists("config.ini")) {
//    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
//  }

  SetDefaultSettings();

  return true;
}


bool SetDataFolder() {
  QDir dataFolder(QDir::currentPath());
  if (!dataFolder.exists("data")) {
    if (!dataFolder.mkdir("data")) return false;
  }
  return true;
}


bool ReadConfigFile() {
  return true;
}


void SetDefaultSettings() {
  ActiveSettings.language = DefaultSettings.language;
  ActiveSettings.dataPath = DefaultSettings.dataPath;
  ActiveSettings.sourceFileName = DefaultSettings.sourceFileName;
  ActiveSettings.targetFileName = DefaultSettings.targetFileName;
}


const QString GetDirectory(const QString &title) {
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
