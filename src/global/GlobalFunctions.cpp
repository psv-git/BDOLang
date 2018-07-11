// Copyright (c) 2018 PSV
// https://github.com/psv-git

#include "GlobalFunctions.hpp"


// service ====================================================================

void Delay(int ms) {
  QEventLoop loop;
  QTimer::singleShot(ms, &loop, &QEventLoop::quit);
  loop.exec();
}

// paths & files ======================================================================

QString GetRootPath() {
  return QDir::currentPath();
}


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


void OpenFile(QFile& file, QFlags<QIODevice::OpenModeFlag> openMode) {
  if (!file.open(openMode)) throw std::runtime_error("opening \"" + file.fileName().toStdString() + "\" file was failed.");
}


void CloseFile(QFile& file) {
  file.close();
  if (file.isOpen()) throw std::runtime_error("closing \"" + file.fileName().toStdString() + "\" file was failed.");
}


void RemoveFile(QFile& file) {
  if (file.isOpen()) file.close();;
  if (!file.remove()) throw std::runtime_error("removing \"" + file.fileName().toStdString() + "\" file was failed.");
}
