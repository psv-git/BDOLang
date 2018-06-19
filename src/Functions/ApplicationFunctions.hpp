#ifndef APPLICATIONFUNCTIONS_HPP
#define APPLICATIONFUNCTIONS_HPP

#include "ApplicationGlobal.hpp"


bool SetupApplication();

bool CreateDataFolder();
void ReadConfigFile(Settings& settings);
bool WriteConfigFile(Settings& settings);
void SetDefaultSettings();

const QString GetDirectoryPath(const QString &title);
const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);


#endif // APPLICATIONFUNCTIONS_HPP
