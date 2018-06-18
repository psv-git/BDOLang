#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ApplicationGlobal.hpp"

namespace Ui { class MainWindow; }
class WindowsHandler;


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(WindowsHandler *parent = 0);
    ~MainWindow();

signals:


public slots:
    void onButtonClick();

private:
    WindowsHandler *parent;
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
