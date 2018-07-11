// Copyright (c) 2018 PSV
// https://github.com/psv-git

#ifndef LANGUAGEWIDGET_HPP
#define LANGUAGEWIDGET_HPP

#include "GlobalClasses.hpp"

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
  LANG m_currentLanguage = LANG::EMPTY;

  void initUi();

};


#endif // LANGUAGEWIDGET_HPP
