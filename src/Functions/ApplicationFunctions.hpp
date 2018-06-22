#ifndef APPLICATIONFUNCTIONS_HPP
#define APPLICATIONFUNCTIONS_HPP

#include "ApplicationGlobal.hpp"


// exceptions =================================================================

void AddException(const QString &exceptionMessage);
void ClearExceptionsList();
const QStringList& GetExceptionsList();

void Delay(int timeToWait);

// application setup ==========================================================

bool SetupApplication();

void ReadConfigFile(Settings &settings);
bool WriteConfigFile(Settings& settings);
void SetDefaultSettings();
QString GetRootPath();

// ============================================================================

const QString GetDirectoryPath(const QString &title);
const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);

// i/o ========================================================================

QDataStream& operator >> (QDataStream& is, LANG& e);
QDataStream& operator << (QDataStream& os, LANG e);

void OpenFile(QFile& file, QFlags<QIODevice::OpenModeFlag> openMode, const QString &functionName = "");
void CloseFile(QFile& file, const QString &functionName = "");
void RemoveFile(QFile& file, const QString& functionName = "");


template <typename V>
void ReadDataFromStream(QDataStream& stream, V& var, size_t size = 0, const QString &functionName = "") {
  if (size == 0) size = sizeof(var);
  stream.readRawData(reinterpret_cast<char*>(&var), size);
  if (stream.status() == QDataStream::ReadCorruptData) {
    AddException("In function \"" + functionName + "\" read data from file was failed.");
    throw;
  }
}


template <typename V>
void WriteDataToStream(QDataStream& stream, V& var, size_t size = 0, const QString &functionName = "") {
  if (size == 0) size = sizeof(var);
  stream.writeRawData(reinterpret_cast<char*>(&var), size);
  if (stream.status() == QDataStream::WriteFailed) {
    AddException("In function \"" + functionName + "\" write data from file was failed.");
    throw;
  }
}


#endif // APPLICATIONFUNCTIONS_HPP
