#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ApplicationFunctions.hpp"

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow {
Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

signals:
  void buttonClicked(MODE mode);

private slots:
  void onButtonClick();

private:
  Ui::MainWindow *ui = nullptr;

};


#endif // MAINWINDOW_H
