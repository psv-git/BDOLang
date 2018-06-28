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
void ReadDataFromStream(QDataStream& stream, V& var, int size = 0, const QString &functionName = "") {
  if (size == 0) size = static_cast<int>(sizeof(var));
  stream.readRawData(reinterpret_cast<char*>(&var), size);
  if (stream.status() == QDataStream::ReadCorruptData) {
    ErrorHandler::getInstance().addException("In function \"" + functionName + "\" read data from file was failed.");
    throw false;
  }
}


template <typename V>
void WriteDataToStream(QDataStream& stream, V& var, int size = 0, const QString &functionName = "") {
  if (size == 0) size = static_cast<int>(sizeof(var));
  stream.writeRawData(reinterpret_cast<char*>(&var), size);
  if (stream.status() == QDataStream::WriteFailed) {
    ErrorHandler::getInstance().addException("In function \"" + functionName + "\" write data from file was failed.");
    throw false;
  }
}


#endif // APPLICATIONFUNCTIONS_HPP
