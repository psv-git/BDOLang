#ifndef LANGUAGEHANDLER_HPP
#define LANGUAGEHANDLER_HPP

#include "Headers.hpp"


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

  void setHandledObjects(QVector<LanguageWidget*> &languageWidgetsList);

  const QMap<LANG, QString>& getLanguagesMap() const;

  LANG toLang(const QString &language) const;
  const QString toString(LANG language) const;
  bool isBlocked(LANG language) const;

  void blockLanguage(LanguageWidget *sender, LANG language);
  void unblockLanguage(LanguageWidget *sender, LANG language);

private:
  LanguageHandler();
  ~LanguageHandler();

  QVector<LanguageWidget*> *languageWidgetsList = nullptr;
  QMap<LANG, QString> languagesMap;
  QVector<LANG> blockedLanguagesList;

};


#endif // LANGUAGEHANDLER_HPP
