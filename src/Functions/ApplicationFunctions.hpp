#ifndef APPLICATIONFUNCTIONS_HPP
#define APPLICATIONFUNCTIONS_HPP

#include "ApplicationGlobal.hpp"


bool SetupApplication();
bool SetDataFolder();
bool ReadConfigFile();
void SetDefaultSettings();
const QString GetDirectory(const QString &title);
const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);


#endif // APPLICATIONFUNCTIONS_HPP
