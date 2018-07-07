#ifndef LANGUAGEHANDLER_HPP
#define LANGUAGEHANDLER_HPP

#include "GlobalFunctions.hpp"

class LanguageWidget;
class ILanguageHandled;


class LanguageHandler {

public:
  static LanguageHandler& getInstance() {
    static LanguageHandler m_instance;
    return m_instance;
  }

  LanguageHandler(LanguageHandler const&) = delete;
  LanguageHandler& operator = (LanguageHandler const&) = delete;

  void setHandledObject(ILanguageHandled *handledObject);

  const QMap<LANG, QString>& getAllLanguages() const;
  const QStringList getAllowedLanguages() const;

  bool isWasBlocking() const;
  LANG getLastChangedLanguage() const;

  LANG toLang(const QString &language) const;
  const QString toString(LANG language) const;
  bool isLanguageBlocked(LANG language) const;

  void blockLanguage(LANG language);
  void unblockLanguage(LANG language);

private:
  LanguageHandler();
  ~LanguageHandler();

  QVector<ILanguageHandled*> m_handledObjectsList;
  QMap<LANG, QString> m_languagesMap;
  QVector<LANG> m_blockedLanguagesList;
  LANG m_lastChangedLanguage = LANG::EMPTY;
  bool m_wasBlocking = false; // is last change was blocking or unblocking?

};


#endif // LANGUAGEHANDLER_HPP
