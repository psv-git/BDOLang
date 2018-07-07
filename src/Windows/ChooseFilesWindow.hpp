#ifndef CHOOSEFILESWINDOW_HPP
#define CHOOSEFILESWINDOW_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class ChooseFilesWindow; }


class ChooseFilesWindow : public QWidget {
Q_OBJECT

public:
  explicit ChooseFilesWindow(QWidget *parent = nullptr);
  ~ChooseFilesWindow();

  void closeEvent(QCloseEvent *event);

signals:
  void buttonClicked(MODE);
  void buttonClicked(const QString &srcFilePath, const QString &targFilePath, LANG language);

public slots:
  void show(MODE mode);

private slots:
  void update();
  void buttonClick();

private:
  Ui::ChooseFilesWindow *m_ui = nullptr;
  SettingsHandler *m_settingsHandler = nullptr;
  LanguageHandler *m_languageHandler = nullptr;
  MODE m_mode = MODE::NONE;
  LANG m_language = LANG::NONE;

  void initUi();
  void addAllowedLanguages();

};


#endif // CHOOSEFILESWINDOW_HPP
