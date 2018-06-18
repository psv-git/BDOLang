#include "ApplicationFunctions.hpp"


bool SetupApplication() {
  // config app =================================
  QDir dataFolder(QDir::currentPath());
  if (!dataFolder.exists("data")) {
    if (!dataFolder.mkdir("data")) return false;
  }

//  QFile configFile(QDir::currentPath());
//  if (!configFile.exists("config.ini")) {
//    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
//  }



  // ============================================

  return true;
}
