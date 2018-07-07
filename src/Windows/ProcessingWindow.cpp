#include "ProcessingWindow.hpp"
#include "ui_ProcessingWindow.h"
#include "DataHandler.hpp"


ProcessingWindow::ProcessingWindow(QWidget *parent) : QWidget(parent), m_ui(new Ui::ProcessingWindow) {
  m_settingsHandler = &SettingsHandler::getInstance();
  m_errorHandler = &ErrorHandler::getInstance();
  initUi();
}


ProcessingWindow::~ProcessingWindow() {
  delete m_ui;
}

// events =====================================================================

bool ProcessingWindow::event(QEvent *event) {
  if (event->type() == QEvent::Close) {
    emit buttonClicked(MODE::CLOSE);
  }
  return QWidget::event(event);
}

// public slots ===============================================================

void ProcessingWindow::show(const QString &srcFilePath, const QString &targFilePath, LANG language, MODE mode) {
  blockWindow();
  QWidget::show();

  DataHandler dataHandler(srcFilePath, targFilePath, language, mode);

  connect(&dataHandler, SIGNAL(started(QString)), this, SLOT(start(QString)));
  connect(&dataHandler, SIGNAL(progressed(int)), m_ui->progressBar, SLOT(setValue(int)));
  connect(&dataHandler, SIGNAL(stopped()), this, SLOT(stop()));
  connect(&dataHandler, SIGNAL(failed()), this, SLOT(fail()));

  dataHandler.run();
}

// private slots ==============================================================

void ProcessingWindow::start(const QString &msg) {
  m_ui->progressBar->setValue(0);
  m_ui->messageLabel->setText(msg);
}


void ProcessingWindow::stop() {
  unblockWindow();
  m_ui->progressBar->setValue(100);
  m_ui->messageLabel->setText("DONE");
}


void ProcessingWindow::fail() {
  m_errorHandler->showMessage();
}


void ProcessingWindow::buttonClick() {
  emit buttonClicked(MODE::CLOSE);
}

// private methods ============================================================

void ProcessingWindow::initUi() {
  m_ui->setupUi(this);

  m_ui->messageLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 20));
  m_ui->exitButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(m_ui->exitButton, SIGNAL(released()), this, SLOT(buttonClick()));

  setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}


void ProcessingWindow::blockWindow() {
  m_ui->exitButton->setEnabled(false);
}


void ProcessingWindow::unblockWindow() {
  m_ui->exitButton->setEnabled(true);
}
