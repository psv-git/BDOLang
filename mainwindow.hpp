#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./src/Global/Global.hpp"
#include "./src/Exceptions/MyException.hpp"
#include "./src/Data/DataHandler.hpp"
#include "./src/Functions/FileFunctions.hpp"


namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow {
Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void onButtonClick(const QString& buttonName);

private:
  Ui::MainWindow *ui;
  DataHandler dataHandler;

};


#endif // MAINWINDOW_H
