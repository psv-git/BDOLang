#include "Settings.hpp"


const DefaultSettings DEFAULT_SETTINGS {
  1,
  1,
  "./data/",
  "languagedata_en.loc",
  "languagedata_ru.loc",
  "languagedata.txt",
  "data",
  "config.ini"
};

//=============================================================================

Settings::Settings() {
  settings = new QSettings(DEFAULT_SETTINGS.configFileName, QSettings::IniFormat);
}


Settings::~Settings() {
  if (settings) delete settings;
}

// public methods =============================================================

void Settings::setSetting(const QString &key, const QVariant &value, bool writeFlag) {
  settings->setValue(key, value);

  if (writeFlag) settings->sync();
}


QVariant Settings::getSetting(const QString &key, const QVariant &defaultValue) {
  return settings->value(key, defaultValue);
}
