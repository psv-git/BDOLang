#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "ApplicationHeaders.hpp"
class QSettings;


struct DefaultSettings {
  int language;
  int compressingLevel;
  QString dataPath;
  QString sourceFileName;
  QString targetFileName;
  QString textFileName;

  QString dataDirectoryName;
  QString configFileName;
};

extern const DefaultSettings DEFAULT_SETTINGS;


class Settings {

public:
  static Settings& getInstance() {
    static Settings instance;
    return instance;
  }

  Settings(Settings const&)              = delete;
  Settings& operator = (Settings const&) = delete;

  void setSetting(const QString &key, const QVariant &value, bool writeFlag);
  QVariant getSetting(const QString &key, const QVariant &defaultValue = QVariant());

private:
  Settings();
  ~Settings();

  QSettings *settings = nullptr;

};


#endif // SETTINGS_HPP
