#ifndef APPLICATIONFUNCTIONS_HPP
#define APPLICATIONFUNCTIONS_HPP

#include "ApplicationGlobal.hpp"

class QApplication;
class QFile;


bool SetupApplication();

void ReadConfigFile(Settings &settings);
bool WriteConfigFile(Settings& settings);
void SetDefaultSettings();
QString GetRootPath();

const QString GetDirectoryPath(const QString &title);
const QString GetFilePath(const QString &title, const QString &extStr);
const QString GetFileName(const QString &title, const QString &extStr);


#endif // APPLICATIONFUNCTIONS_HPP
