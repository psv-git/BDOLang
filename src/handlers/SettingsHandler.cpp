// Copyright (c) 2018 PSV
// https://github.com/psv-git

#include "SettingsHandler.hpp"


SettingsHandler::SettingsHandler() {
  m_settings = new QSettings(DEFAULT_SETTINGS.configFileName, QSettings::IniFormat);
}


SettingsHandler::~SettingsHandler() {
  if (m_settings) m_settings->deleteLater();
  if (m_fontsList) delete m_fontsList;
}

// public methods =============================================================

QStringList SettingsHandler::getGroups() {
  return m_settings->childGroups();
}


QVariant SettingsHandler::getSetting(const QString &group, const QString &key, const QVariant &defaultValue) {
  if (!group.isEmpty()) m_settings->beginGroup(group);
  QVariant value = m_settings->value(key, defaultValue);
  if (!group.isEmpty()) m_settings->endGroup();
  return value;
}


void SettingsHandler::setSetting(const QString &group, const QString &key, const QVariant &value) {
  if (!group.isEmpty()) m_settings->beginGroup(group);
  m_settings->setValue(key, value);
  if (!group.isEmpty()) m_settings->endGroup();
}


void SettingsHandler::removeSetting(const QString &key) {
  m_settings->remove(key);
}


QFont SettingsHandler::getFont(const QString &family, const QString &style, int pointSize) {
  return m_fontsList->font(family, style, pointSize);
}


void SettingsHandler::setFonts() {
  if (!m_fontsList) m_fontsList = new QFontDatabase();
  m_fontsList->addApplicationFont(":/fonts/fonts/LiberationMono-Bold.ttf");
  m_fontsList->addApplicationFont(":/fonts/fonts/LiberationMono-Regular.ttf");
  m_fontsList->addApplicationFont(":/fonts/fonts/LiberationSans-Bold.ttf");
  m_fontsList->addApplicationFont(":/fonts/fonts/LiberationSans-Regular.ttf");
}


void SettingsHandler::saveSettings() {
  m_settings->sync();
}
