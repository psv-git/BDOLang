#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}


MainWindow::~MainWindow() {
  delete ui;
}

// ============================================================================

void onButtonClick(const QString& buttonName) {
  switch (buttonName) {
    case binToTextButton:
      dataHandler.readDataFromFile();
      break;
  }
}

