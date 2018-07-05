#ifndef LANGUAGEWIDGET_HPP
#define LANGUAGEWIDGET_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class LanguageWidget; }


class LanguageWidget : public QWidget {
Q_OBJECT

public:
  explicit LanguageWidget(QWidget *parent = 0);
  ~LanguageWidget();

  bool needToDelete();
  void setDeletable(bool value);
  void setLanguage(LANG language);
  void setLocFileName(const QString &fileName);
  void setTextFileName(const QString &fileName);

  void save();
  void updateLanguage();

private slots:
  void update();
  void buttonClick();

private:
  Ui::LanguageWidget *m_ui = nullptr;
  SettingsHandler *m_settingsHandler = nullptr;
  LanguageHandler *m_languageHandler = nullptr;
  LANG m_currentLanguage = LANG::EMPTY;

  void initUi();

};


#endif // LANGUAGEWIDGET_HPP
