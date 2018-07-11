// Copyright (c) 2018 PSV
// https://github.com/psv-git

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GlobalClasses.hpp"

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow {
Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

signals:
  void buttonClicked(MODE mode);

public slots:
  void unlockWindow();

private slots:
  void lockWindow();
  void buttonClick();

private:
  Ui::MainWindow *m_ui = nullptr;

  void initUi();

};


#endif // MAINWINDOW_H
