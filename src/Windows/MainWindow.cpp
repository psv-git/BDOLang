#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "MyButton.hpp"
#include "WindowsHandler.hpp"


MainWindow::MainWindow(WindowsHandler *parent) : ui(new Ui::MainWindow) {
  MainWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->button1, &MyButton::released, this, &MainWindow::onButtonClick);
  connect(ui->button2, &MyButton::released, this, &MainWindow::onButtonClick);
  connect(ui->button3, &MyButton::released, this, &MainWindow::onButtonClick);
  connect(ui->settingsButton, &MyButton::released, this, &MainWindow::onButtonClick);
  connect(ui->exitButton, &MyButton::released, this, &MainWindow::onButtonClick);
}


MainWindow::~MainWindow() {
  delete ui;
}

// ===========================================================================

void MainWindow::onButtonClick() {
  QObject *obj = sender();
  QString objName = obj->objectName();
  if (objName == "exitButton") parent->onButtonClick(this, MODE::EXIT);
  if (objName == "settingsButton") parent->onButtonClick(this, MODE::SETTINGS);
  if (objName == "button1") parent->onButtonClick(this, MODE::MERGE);
  if (objName == "button2") parent->onButtonClick(this, MODE::BIN_TO_TEXT);
  if (objName == "button3") parent->onButtonClick(this, MODE::TRANSLATE);
}
