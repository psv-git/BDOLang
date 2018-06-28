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

QStringList Settings::getGroups() {
  return settings->childGroups();
}


QVariant Settings::getSetting(const QString &group, const QString &key, const QVariant &defaultValue) {
  if (!group.isEmpty()) settings->beginGroup(group);
  QVariant value = settings->value(key, defaultValue);
  if (!group.isEmpty()) settings->endGroup();
  return value;
}


void Settings::setSetting(const QString &group, const QString &key, const QVariant &value) {
  if (!group.isEmpty()) settings->beginGroup(group);
  settings->setValue(key, value);
  if (!group.isEmpty()) settings->endGroup();
}


void Settings::removeSetting(const QString &key) {
  settings->remove(key);
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
