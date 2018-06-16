#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"


MainWindow::MainWindow(WindowsHandler *parent) : ui(new Ui::MainWindow) {
  MainWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->button1, &MyButton::released, this, &MainWindow::onButtonClick);
  connect(ui->button2, &MyButton::released, this, &MainWindow::onButtonClick);
  connect(ui->button3, &MyButton::released, this, &MainWindow::onButtonClick);
}


MainWindow::~MainWindow() {
  delete ui;
}

// ===========================================================================

void MainWindow::onButtonClick() {
  MyButton* button = qobject_cast<MyButton*>(sender());
  if (button != NULL ) {
    QString name = button->objectName();
    if (name == "button1") parent->onButtonClick(this, 1);
  }
}
