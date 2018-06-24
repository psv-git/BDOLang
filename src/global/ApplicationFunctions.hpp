#ifndef APPLICATIONFUNCTIONS_HPP
#define APPLICATIONFUNCTIONS_HPP

#include "ApplicationGlobal.hpp"


// exceptions =================================================================

void AddException(const QString &exceptionMessage);
const QString GetExceptionsMessage();

// service ====================================================================

void Delay(int timeToWait);

const QString GetDirectoryPath(const QString &title);
QString GetRootPath();

QFont GetFont(const QString &family, const QString &style, int pointSize);

// files ======================================================================

const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);

void OpenFile(QFile& file,   QFlags<QIODevice::OpenModeFlag> openMode, const QString &functionName = "");
void CloseFile(QFile& file,  const QString &functionName = "");
void RemoveFile(QFile& file, const QString& functionName = "");

// application setup ==========================================================

bool SetupApplication();
void SetFonts(QFontDatabase &fontsDataBase);

// i/o ========================================================================

template <typename V>
void ReadDataFromStream(QDataStream& stream, V& var, int size = 0, const QString &functionName = "") {
  if (size == 0) size = static_cast<int>(sizeof(var));
  stream.readRawData(reinterpret_cast<char*>(&var), size);
  if (stream.status() == QDataStream::ReadCorruptData) {
    AddException("In function \"" + functionName + "\" read data from file was failed.");
    throw;
  }
}


template <typename V>
void WriteDataToStream(QDataStream& stream, V& var, int size = 0, const QString &functionName = "") {
  if (size == 0) size = static_cast<int>(sizeof(var));
  stream.writeRawData(reinterpret_cast<char*>(&var), size);
  if (stream.status() == QDataStream::WriteFailed) {
    AddException("In function \"" + functionName + "\" write data from file was failed.");
    throw;
  }
}


#endif // APPLICATIONFUNCTIONS_HPP
