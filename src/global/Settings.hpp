#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "ApplicationGlobal.hpp"
class QSettings;
class QFontDatabase;


struct DefaultSettings {
  int compressingLevel;
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

  QVariant getSetting(const QString &key, const QVariant &defaultValue = QVariant());
  QFont getFont(const QString &family, const QString &style, int pointSize);

  void setSetting(const QString &key, const QVariant &value);
  void setFonts();

  void saveSettings();

private:
  Settings();
  ~Settings();

  QSettings *settings      = nullptr;
  QFontDatabase *fontsList = nullptr;

};


#endif // SETTINGS_HPP
