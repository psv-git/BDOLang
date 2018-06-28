#ifndef LANGUAGEHANDLER_HPP
#define LANGUAGEHANDLER_HPP

#include "Headers.hpp"
#include "ILanguageHandled.hpp"


enum LANG : int { EMPTY, EN, AR, BE, EL, DA, IW, ES, IT, ZH, KO, DE, RU, TR, UK, FR, JA };
Q_DECLARE_METATYPE(LANG)

class LanguageWidget;


class LanguageHandler {

public:
  static LanguageHandler& getInstance() {
    static LanguageHandler instance;
    return instance;
  }

  LanguageHandler(LanguageHandler const&)              = delete;
  LanguageHandler& operator = (LanguageHandler const&) = delete;

  void setHandledObject(ILanguageHandled *handledObject);

  const QMap<LANG, QString>& getLanguagesMap() const;

  bool isWasBlocking() const;
  LANG getLastChangedLanguage() const;

  LANG toLang(const QString &language)  const;
  const QString toString(LANG language) const;
  bool isLanguageBlocked(LANG language) const;

  void blockLanguage(LANG language);
  void unblockLanguage(LANG language);

private:
  LanguageHandler();
  ~LanguageHandler();

  QVector<ILanguageHandled*> handledObjectsList;

  QMap<LANG, QString> languagesMap;
  QVector<LANG> blockedLanguagesList;

  LANG lastChangedLanguage = LANG::EMPTY;
  bool wasBlocking = false; // is last change was blocking or unblocking?

};


#endif // LANGUAGEHANDLER_HPP
