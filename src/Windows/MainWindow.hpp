#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ApplicationGlobal.hpp"
#include <QMainWindow>

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
  SettingsHandler *m_settingsHandler = nullptr;

  void initUi();

};


#endif // MAINWINDOW_H
