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
  void buttonClicked(const QString &srcFilePath, const QString &targFilePath);

public slots:
  void show(MODE mode);

private slots:
  void update();
  void buttonClick();

private:
  Ui::ChooseFilesWindow *ui = nullptr;
  Settings *settings = nullptr;
  LanguageHandler *languageHandler = nullptr;
  MODE mode = MODE::NONE;

  void initUi();
  void addAllowedLanguages();

};


#endif // CHOOSEFILESWINDOW_HPP
