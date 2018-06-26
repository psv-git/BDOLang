#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ApplicationGlobal.hpp"

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
  Ui::MainWindow *ui = nullptr;
  Settings *settings = nullptr;

};


#endif // MAINWINDOW_H
