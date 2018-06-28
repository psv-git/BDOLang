#include <QSettings>
#include <QFontDatabase>
#include "Settings.hpp"


const DefaultSettings DEFAULT_SETTINGS {
  1,
  "data",
  "config.ini"
};

//=============================================================================

Settings::Settings() {
  settings = new QSettings(DEFAULT_SETTINGS.configFileName, QSettings::IniFormat);
}


Settings::~Settings() {
  if (settings) settings->deleteLater();
  if (fontsList) delete fontsList;
}

// public methods =============================================================

QMap<QString, QPair<QString, QString>> Settings::getLanguageWidgetsSettings() {
  QMap<QString, QPair<QString, QString>> languagesMap;
  QStringList groups = settings->childGroups();
  for (int i = 0; i < groups.size(); i++) {
    settings->beginGroup(groups[i]);
    if (settings->contains("loc_file_name") && settings->contains("text_file_name")) {
      languagesMap.insert(groups[i], QPair<QString, QString>(settings->value("loc_file_name", "").toString(), settings->value("text_file_name", "").toString()));
    }
    settings->endGroup();
  }
  return languagesMap;
}


QVariant Settings::getSetting(const QString &group, const QString &key, const QVariant &defaultValue) {
  if (!group.isEmpty()) settings->beginGroup(group);
  QVariant value = settings->value(key, defaultValue);
  if (!settings->group().isEmpty()) settings->endGroup();
  return value;
}


void Settings::setSetting(const QString &group, const QString &key, const QVariant &value) {
  if (!group.isEmpty()) settings->beginGroup(group);
  settings->setValue(key, value);
  if (!settings->group().isEmpty()) settings->endGroup();
}


QFont Settings::getFont(const QString &family, const QString &style, int pointSize) {
  return fontsList->font(family, style, pointSize);
}


void Settings::setFonts() {
  if (!fontsList) fontsList = new QFontDatabase();
  fontsList->addApplicationFont(":/fonts/fonts/LiberationMono-Bold.ttf");
  fontsList->addApplicationFont(":/fonts/fonts/LiberationMono-Regular.ttf");
  fontsList->addApplicationFont(":/fonts/fonts/LiberationSans-Bold.ttf");
  fontsList->addApplicationFont(":/fonts/fonts/LiberationSans-Regular.ttf");
}


void Settings::saveSettings() {
  settings->sync();
}
