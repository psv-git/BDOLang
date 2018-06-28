#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Headers.hpp"
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
  Settings(Settings const&) = delete;
  Settings& operator = (Settings const&) = delete;

  QMap<QString, QPair<QString, QString>> getLanguageWidgetsSettings();

  QVariant getSetting(const QString &group, const QString &key, const QVariant &defaultValue);
  void setSetting(const QString &group, const QString &key, const QVariant &value);

  QFont getFont(const QString &family, const QString &style, int pointSize);
  void setFonts();

  void saveSettings();

private:
  Settings();
  ~Settings();

  QSettings *settings = nullptr;
  QFontDatabase *fontsList = nullptr;

};


#endif // SETTINGS_HPP
