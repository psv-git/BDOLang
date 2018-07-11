// Copyright (c) 2018 PSV
// https://github.com/psv-git

#ifndef GLOBALFUNCTIONS_HPP
#define GLOBALFUNCTIONS_HPP

// THIS FILE INCLUDED IN GlobalClasses.hpp

#include "GlobalVariables.hpp"


// service ====================================================================

void Delay(int ms);

// paths & files ======================================================================

QString GetRootPath();

const QString GetDirectoryPath(const QString &title);
const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);

void OpenFile(QFile& file, QFlags<QIODevice::OpenModeFlag> openMode);
void CloseFile(QFile& file);
void RemoveFile(QFile& file);

// i/o ========================================================================

template <typename V>
int ReadDataFromStream(QDataStream& stream, V& var, int size = 0) {
  if (size == 0) size = static_cast<int>(sizeof(var));
  int count = stream.readRawData(reinterpret_cast<char*>(&var), size);
  if (count < 0) throw std::ios_base::failure("reading data from file was failed");
  return count;
}


template <typename V>
int WriteDataToStream(QDataStream& stream, V& var, int size = 0) {
  if (size == 0) size = static_cast<int>(sizeof(var));
  int count = stream.writeRawData(reinterpret_cast<char*>(&var), size);
  if (count < 0) throw std::ios_base::failure("writing data to file was failed");
  return count;
}


#endif // GLOBALFUNCTIONS_HPP
