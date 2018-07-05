#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "WindowsHandler.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
  m_settingsHandler = &SettingsHandler::getInstance();
  initUi();
}


MainWindow::~MainWindow() {
  delete m_ui;
}

// public slots ===============================================================

void MainWindow::unlockWindow() {
  m_ui->glass->hide();
}

// private slots ==============================================================

void MainWindow::lockWindow() {
  m_ui->glass->show();
}

void MainWindow::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "bttButton") emit buttonClicked(MODE::BIN_TO_TEXT);
  else if (objName == "ttbButton") emit buttonClicked(MODE::TEXT_TO_BIN);
  else if (objName == "mbButton") emit buttonClicked(MODE::MERGE_BIN);
  else if (objName == "mtButton") emit buttonClicked(MODE::MERGE_TEXT);
  else if (objName == "settingsButton") emit buttonClicked(MODE::SETTINGS);
  else if (objName == "exitButton") emit buttonClicked(MODE::EXIT);
}

// private methods ============================================================

void MainWindow::initUi() {
  m_ui->setupUi(this);

  m_ui->bttButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->ttbButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->mbButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->mtButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->settingsButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->exitButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(m_ui->bttButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->ttbButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->mbButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->mtButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->settingsButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->exitButton, SIGNAL(released()), this, SLOT(buttonClick()));

  connect(this, SIGNAL(buttonClicked(MODE)), this, SLOT(lockWindow()));

  unlockWindow();
}
