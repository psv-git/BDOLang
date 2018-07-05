#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include "ApplicationFunctions.hpp"
#include "ILanguageHandled.hpp"

namespace Ui { class SettingsWindow; }


class SettingsWindow : public QWidget, public ILanguageHandled {
Q_OBJECT

public:
  explicit SettingsWindow(QWidget *parent = nullptr);
  ~SettingsWindow();

  virtual void updateLanguage();

protected:
  void closeEvent(QCloseEvent *event);

signals:
  void buttonClicked(MODE mode);

public slots:
  void show();

private slots:
  void buttonClick();

private:
  Ui::SettingsWindow *m_ui = nullptr;
  SettingsHandler *m_settingsHandler = nullptr;
  LanguageHandler *m_languageHandler = nullptr;

  QVector<LanguageWidget*> m_languageWidgetsList;

  void initUi();
  void addLanguageWidgets();
  void addLanguageWidget(bool deletable, LANG language, const QString &locFileName, const QString &textFileName);
  void deleteLanguageWidgets();

};


#endif // SETTINGSWINDOW_HPP
