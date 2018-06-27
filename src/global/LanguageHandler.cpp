#include "LanguageHandler.hpp"
#include "SettingsWindow.hpp"
#include "LanguageWidget.hpp"


LanguageHandler::LanguageHandler() {
  languagesMap.insert(LANG::EMPTY, "");
  languagesMap.insert(LANG::EN, "EN");
  languagesMap.insert(LANG::AR, "AR");
  languagesMap.insert(LANG::BE, "BE");
  languagesMap.insert(LANG::EL, "EL");
  languagesMap.insert(LANG::DA, "DA");
  languagesMap.insert(LANG::IW, "IW");
  languagesMap.insert(LANG::ES, "ES");
  languagesMap.insert(LANG::IT, "IT");
  languagesMap.insert(LANG::ZH, "ZH");
  languagesMap.insert(LANG::KO, "KO");
  languagesMap.insert(LANG::DE, "DE");
  languagesMap.insert(LANG::RU, "RU");
  languagesMap.insert(LANG::TR, "TR");
  languagesMap.insert(LANG::UK, "UK");
  languagesMap.insert(LANG::FR, "FR");
  languagesMap.insert(LANG::JA, "JA");
}


LanguageHandler::~LanguageHandler() {}

// public methods =============================================================

void LanguageHandler::setHandledObjects(QVector<LanguageWidget*> &languageWidgetsList) {
  this->languageWidgetsList = &languageWidgetsList;
}


const QMap<LANG, QString>& LanguageHandler::getLanguagesMap() const {
  return languagesMap;
}


LANG LanguageHandler::toLang(const QString &language) const {
  return languagesMap.key(language, LANG::EMPTY);
}


const QString LanguageHandler::toString(LANG language) const {
  return languagesMap.value(language, "");
}


bool LanguageHandler::isBlocked(LANG language) const {
  return blockedLanguagesList.contains(language);
}


void LanguageHandler::blockLanguage(LanguageWidget *sender, LANG language) {
  if (!blockedLanguagesList.contains(language)) {
    blockedLanguagesList.push_back(language);
    for (int i = 0; i < languageWidgetsList->size(); i++) {
      if (languageWidgetsList->at(i) != sender) {
        languageWidgetsList->at(i)->removeLanguage(language);
      }
    }
  }
}


void LanguageHandler::unblockLanguage(LanguageWidget *sender, LANG language) {
  blockedLanguagesList.removeOne(language);
  for (int i = 0; i < languageWidgetsList->size(); i++) {
    if (languageWidgetsList->at(i) != sender) {
      languageWidgetsList->at(i)->addLanguage(language);
    }
  }
}
