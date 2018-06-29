#include "LanguageHandler.hpp"
#include "SettingsWindow.hpp"
#include "LanguageWidget.hpp"
#include "ILanguageHandled.hpp"


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

void LanguageHandler::setHandledObject(ILanguageHandled *handledObject) {
  handledObjectsList.push_back(handledObject);
}


const QMap<LANG, QString>& LanguageHandler::getAllLanguages() const {
  return languagesMap;
}


const QStringList LanguageHandler::getAllowedLanguages() const {
  QStringList allowedLanguagesMap;
  for (auto language : languagesMap.keys()) {
    if (isLanguageBlocked(language)) {
      allowedLanguagesMap.push_back(languagesMap.value(language, ""));
    }
  }
  return allowedLanguagesMap;
}


bool LanguageHandler::isWasBlocking() const {
  return wasBlocking;
}


LANG LanguageHandler::getLastChangedLanguage() const {
  return lastChangedLanguage;
}


LANG LanguageHandler::toLang(const QString &language) const {
  return languagesMap.key(language, LANG::NONE);
}


const QString LanguageHandler::toString(LANG language) const {
  return languagesMap.value(language, "");
}


bool LanguageHandler::isLanguageBlocked(LANG language) const {
  return blockedLanguagesList.contains(language);
}


void LanguageHandler::blockLanguage(LANG language) {
  if (language != LANG::EMPTY) {
    if (!blockedLanguagesList.contains(language)) {
      wasBlocking = true;
      lastChangedLanguage = language;
      blockedLanguagesList.push_back(language);
      for (int i = 0; i < handledObjectsList.size(); i++) {
        handledObjectsList[i]->updateLanguage();
      }
    }
  }
}


void LanguageHandler::unblockLanguage(LANG language) {
  if (language != LANG::EMPTY) {
    wasBlocking = false;
    lastChangedLanguage = language;
    blockedLanguagesList.removeOne(language);
    for (int i = 0; i < handledObjectsList.size(); i++) {
      handledObjectsList[i]->updateLanguage();
    }
  }
}
