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

QVariant Settings::getSetting(const QString &key, const QVariant &defaultValue) {
  return settings->value(key, defaultValue);
}


QFont Settings::getFont(const QString &family, const QString &style, int pointSize) {
  return fontsList->font(family, style, pointSize);
}


void Settings::setSetting(const QString &key, const QVariant &value) {
  settings->setValue(key, value);
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
