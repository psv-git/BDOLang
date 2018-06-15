#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "mybutton.hpp"


namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow {
Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

signals:


public slots:
  void onButtonClick();

private:
  Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
