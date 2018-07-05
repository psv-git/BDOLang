#ifndef SETTINGSHANDLER_HPP
#define SETTINGSHANDLER_HPP

#include "headers.hpp"
class QSettings;
class QFontDatabase;


struct DefaultSettings {
  int compressingLevel;
  QString dataDirectoryName;
  QString configFileName;
};

extern const DefaultSettings DEFAULT_SETTINGS;


class SettingsHandler {

public:
  static SettingsHandler& getInstance() {
    static SettingsHandler m_instance;
    return m_instance;
  }

  SettingsHandler(SettingsHandler const&) = delete;
  SettingsHandler& operator = (SettingsHandler const&) = delete;

  QStringList getGroups();

  QVariant getSetting(const QString &group, const QString &key, const QVariant &defaultValue);
  void setSetting(const QString &group, const QString &key, const QVariant &value);
  void removeSetting(const QString &key);

  QFont getFont(const QString &family, const QString &style, int pointSize);
  void setFonts();

  void saveSettings();

private:
  SettingsHandler();
  ~SettingsHandler();

  QSettings *m_settings = nullptr;
  QFontDatabase *m_fontsList = nullptr;

};


#endif // SETTINGSHANDLER_HPP
