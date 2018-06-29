#ifndef APPLICATIONFUNCTIONS_HPP
#define APPLICATIONFUNCTIONS_HPP

#include "ApplicationGlobal.hpp"


// service ====================================================================

int RunApplication(int argc, char *argv[]);

void Delay(int ms);

// paths & files ======================================================================

const QString GetDirectoryPath(const QString &title);
QString GetRootPath();

const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);

void OpenFile(QFile& file,   QFlags<QIODevice::OpenModeFlag> openMode, const QString &functionName = "");
void CloseFile(QFile& file,  const QString &functionName = "");
void RemoveFile(QFile& file, const QString& functionName = "");

// i/o ========================================================================

template <typename V>
int ReadDataFromStream(QDataStream& stream, V& var, int size = 0, const QString &functionName = "") {
  if (size == 0) size = static_cast<int>(sizeof(var));
  int count = stream.readRawData(reinterpret_cast<char*>(&var), size);
  if (count < 0) {
    ErrorHandler::getInstance().addException("In function \"" + functionName + "\" read data from file was failed.");
    throw false;
  }
  return count;
}


template <typename V>
int WriteDataToStream(QDataStream& stream, V& var, int size = 0, const QString &functionName = "") {
  if (size == 0) size = static_cast<int>(sizeof(var));
  int count = stream.writeRawData(reinterpret_cast<char*>(&var), size);
  if (count < 0) {
    ErrorHandler::getInstance().addException("In function \"" + functionName + "\" write data from file was failed.");
    throw false;
  }
  return count;
}


#endif // APPLICATIONFUNCTIONS_HPP
