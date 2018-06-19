#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "WindowsHandler.hpp"


MainWindow::MainWindow(WindowsHandler *parent) : ui(new Ui::MainWindow) {
  MainWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->button1, &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->button2, &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->button3, &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->button4, &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->settingsButton, &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->exitButton, &QPushButton::released, this, &MainWindow::onButtonClick);
}


MainWindow::~MainWindow() {
  delete ui;
}

// ===========================================================================

void MainWindow::onButtonClick() {
  QObject *obj = sender();
  QString objName = obj->objectName();
  if (objName == "button1") parent->onButtonClick(this, MODE::BIN_TO_TEXT);
  if (objName == "button2") parent->onButtonClick(this, MODE::TEXT_TO_BIN);
  if (objName == "button3") parent->onButtonClick(this, MODE::MERGE);
  if (objName == "button4") parent->onButtonClick(this, MODE::TRANSLATE);
  if (objName == "settingsButton") parent->onButtonClick(this, MODE::SETTINGS);
  if (objName == "exitButton") parent->onButtonClick(this, MODE::EXIT);
}
