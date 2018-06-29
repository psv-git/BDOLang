#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "WindowsHandler.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  settings = &Settings::getInstance();
  initUi();
}


MainWindow::~MainWindow() {
  delete ui;
}

// public slots ===============================================================

void MainWindow::unlockWindow() {
  ui->glass->hide();
}

// private slots ==============================================================

void MainWindow::lockWindow() {
  ui->glass->show();
}

void MainWindow::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "bttButton") emit buttonClicked(MODE::BIN_TO_TEXT);
  else if (objName == "ttbButton") emit buttonClicked(MODE::TEXT_TO_BIN);
  else if (objName == "mbButton") emit buttonClicked(MODE::MERGE_BIN);
  else if (objName == "mtButton") emit buttonClicked(MODE::MERGE_TEXT);
  else if (objName == "cbsiButton") emit buttonClicked(MODE::COMP_BY_SIZE);
  else if (objName == "cbstButton") emit buttonClicked(MODE::COMP_BY_STR);
  else if (objName == "trButton") emit buttonClicked(MODE::TRANSLATE);
  else if (objName == "settingsButton") emit buttonClicked(MODE::SETTINGS);
  else if (objName == "exitButton") emit buttonClicked(MODE::EXIT);
}

// private methods ============================================================

void MainWindow::initUi() {
  ui->setupUi(this);

  ui->bttButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->ttbButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->mbButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->mtButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->cbsiButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->cbstButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->trButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->settingsButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->exitButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));

  connect(ui->bttButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->ttbButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->mbButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->mtButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cbsiButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cbstButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->trButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->settingsButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->exitButton, SIGNAL(released()), this, SLOT(buttonClick()));

  connect(this, SIGNAL(buttonClicked(MODE)), this, SLOT(lockWindow()));

  unlockWindow();
}
