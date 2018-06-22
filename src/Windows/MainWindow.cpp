#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "WindowsHandler.hpp"


MainWindow::MainWindow(WindowsHandler *parent) : ui(new Ui::MainWindow) {
  MainWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->bttButton,      &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->ttbButton,      &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->mbButton,       &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->mtButton,       &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->transButton,    &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->compButton,     &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->settingsButton, &QPushButton::released, this, &MainWindow::onButtonClick);
  connect(ui->exitButton,     &QPushButton::released, this, &MainWindow::onButtonClick);
}


MainWindow::~MainWindow() {
  delete ui;
}

// ===========================================================================

void MainWindow::onButtonClick() {
  QObject *obj = sender();
  QString objName = obj->objectName();
  if (objName == "bttButton")      parent->onButtonClick(this, MODE::BIN_TO_TEXT);
  if (objName == "ttbButton")      parent->onButtonClick(this, MODE::TEXT_TO_BIN);
  if (objName == "mbButton")       parent->onButtonClick(this, MODE::MERGE_BIN);
  if (objName == "mtButton")       parent->onButtonClick(this, MODE::MERGE_TEXT);
  if (objName == "transButton")    parent->onButtonClick(this, MODE::TRANSLATE);
  if (objName == "compButton")     parent->onButtonClick(this, MODE::COMPARE);
  if (objName == "settingsButton") parent->onButtonClick(this, MODE::SETTINGS);
  if (objName == "exitButton")     parent->onButtonClick(this, MODE::EXIT);
}
