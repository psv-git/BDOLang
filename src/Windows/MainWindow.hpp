#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ApplicationGlobal.hpp"

namespace Ui { class MainWindow; }
class WindowsHandler;


class MainWindow : public QMainWindow {
Q_OBJECT

public:
  explicit MainWindow(WindowsHandler *parent = nullptr);
  ~MainWindow();

signals:


public slots:
  void onButtonClick();

private:
  WindowsHandler *parent = nullptr;
  Ui::MainWindow *ui     = nullptr;

};


#endif // MAINWINDOW_H
