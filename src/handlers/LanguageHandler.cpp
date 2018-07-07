#include "LanguageHandler.hpp"
#include "LanguageWidget.hpp"
#include "ILanguageHandled.hpp"


LanguageHandler::LanguageHandler() {
  m_languagesMap.insert(LANG::EMPTY, "");
  m_languagesMap.insert(LANG::EN, "EN");
  m_languagesMap.insert(LANG::AR, "AR");
  m_languagesMap.insert(LANG::BE, "BE");
  m_languagesMap.insert(LANG::EL, "EL");
  m_languagesMap.insert(LANG::DA, "DA");
  m_languagesMap.insert(LANG::IW, "IW");
  m_languagesMap.insert(LANG::ES, "ES");
  m_languagesMap.insert(LANG::IT, "IT");
  m_languagesMap.insert(LANG::ZH, "ZH");
  m_languagesMap.insert(LANG::KO, "KO");
  m_languagesMap.insert(LANG::DE, "DE");
  m_languagesMap.insert(LANG::RU, "RU");
  m_languagesMap.insert(LANG::TR, "TR");
  m_languagesMap.insert(LANG::UK, "UK");
  m_languagesMap.insert(LANG::FR, "FR");
  m_languagesMap.insert(LANG::JA, "JA");
}


LanguageHandler::~LanguageHandler() {}

// public methods =============================================================

void LanguageHandler::setHandledObject(ILanguageHandled *handledObject) {
  m_handledObjectsList.push_back(handledObject);
}


const QMap<LANG, QString>& LanguageHandler::getAllLanguages() const {
  return m_languagesMap;
}


const QStringList LanguageHandler::getAllowedLanguages() const {
  QStringList allowedLanguagesMap;
  for (auto language : m_languagesMap.keys()) {
    if (isLanguageBlocked(language)) {
      allowedLanguagesMap.push_back(m_languagesMap.value(language, ""));
    }
  }
  return allowedLanguagesMap;
}


bool LanguageHandler::isWasBlocking() const {
  return m_wasBlocking;
}


LANG LanguageHandler::getLastChangedLanguage() const {
  return m_lastChangedLanguage;
}


LANG LanguageHandler::toLang(const QString &language) const {
  return m_languagesMap.key(language, LANG::NONE);
}


const QString LanguageHandler::toString(LANG language) const {
  return m_languagesMap.value(language, "");
}


bool LanguageHandler::isLanguageBlocked(LANG language) const {
  return m_blockedLanguagesList.contains(language);
}


void LanguageHandler::blockLanguage(LANG language) {
  if (language != LANG::EMPTY) {
    if (!m_blockedLanguagesList.contains(language)) {
      m_wasBlocking = true;
      m_lastChangedLanguage = language;
      m_blockedLanguagesList.push_back(language);
      for (int i = 0; i < m_handledObjectsList.size(); i++) {
        m_handledObjectsList[i]->updateLanguage();
      }
    }
  }
}


void LanguageHandler::unblockLanguage(LANG language) {
  if (language != LANG::EMPTY) {
    m_wasBlocking = false;
    m_lastChangedLanguage = language;
    m_blockedLanguagesList.removeOne(language);
    for (int i = 0; i < m_handledObjectsList.size(); i++) {
      m_handledObjectsList[i]->updateLanguage();
    }
  }
}
