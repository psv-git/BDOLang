#ifndef CHOOSEFILESWINDOW_HPP
#define CHOOSEFILESWINDOW_HPP

#include "GlobalClasses.hpp"

namespace Ui { class ChooseFilesWindow; }


class ChooseFilesWindow : public QWidget {
Q_OBJECT

public:
  explicit ChooseFilesWindow(QWidget *parent = nullptr);
  ~ChooseFilesWindow();

  bool event(QEvent* event);

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
  MODE m_mode = MODE::NONE;
  LANG m_language = LANG::NONE;

  void initUi();
  void addAllowedLanguages();

};


#endif // CHOOSEFILESWINDOW_HPP
