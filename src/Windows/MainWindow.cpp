#include "MainWindow.hpp"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
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
  else if (objName == "ftsButton") emit buttonClicked(MODE::FILL_TO_SIZE);
  else if (objName == "settingsButton") emit buttonClicked(MODE::SETTINGS);
  else if (objName == "exitButton") emit buttonClicked(MODE::EXIT);
}

// private methods ============================================================

void MainWindow::initUi() {
  m_ui->setupUi(this);

  m_ui->bttButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->ttbButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->mbButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->mtButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->ftsButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->settingsButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->exitButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));

  m_ui->label1->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Regular", 10));
  m_ui->label2->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Regular", 10));
  m_ui->label3->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Regular", 10));

  connect(m_ui->bttButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->ttbButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->mbButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->mtButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->ftsButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->settingsButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->exitButton, SIGNAL(released()), this, SLOT(buttonClick()));

  connect(this, SIGNAL(buttonClicked(MODE)), this, SLOT(lockWindow()));

  unlockWindow();
}
