#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "mybutton.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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
    if (name == "button1") button->setText("button1");
    if (name == "button2") button->setText("button2");
    if (name == "button3") button->setText("button3");
  }
}
