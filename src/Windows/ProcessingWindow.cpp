#include <QThread>
#include "ProcessingWindow.hpp"
#include "ui_ProcessingWindow.h"
#include "DataHandler.hpp"


ProcessingWindow::ProcessingWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ProcessingWindow) {
  settings = &Settings::getInstance();
  errorHandler = &ErrorHandler::getInstance();
  initUi();
}


ProcessingWindow::~ProcessingWindow() {
  delete ui;
}

// events =====================================================================

void ProcessingWindow::closeEvent(QCloseEvent *event) {
  // TODO: kill thread there
  emit buttonClicked(MODE::CLOSE);
  QWidget::closeEvent(event);
}

// public slots ===============================================================

void ProcessingWindow::show(const QString &srcFilePath, const QString &targFilePath, MODE mode) {
  this->blockSignals(true);
  ui->exitButton->setEnabled(false);
  ui->messageLabel->setText("PROCESSING");
  QWidget::show();

  // work on another thread
  thread = new QThread;
  DataHandler* dataHandler = new DataHandler(srcFilePath, targFilePath, mode);

  dataHandler->moveToThread(thread);
  connect(thread, SIGNAL(started()), dataHandler, SLOT(start()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), this, SLOT(complete()));

  connect(dataHandler, SIGNAL(failed()), this, SLOT(error()));
  connect(dataHandler, SIGNAL(completed()), thread, SLOT(quit()));
  connect(dataHandler, SIGNAL(completed()), dataHandler, SLOT(deleteLater()));

  thread->start();
}

// private slots ==============================================================

void ProcessingWindow::error() {
  errorHandler->showMessage();
}

void ProcessingWindow::complete() {
  ui->exitButton->setEnabled(true);
  ui->messageLabel->setText("DONE");
  this->blockSignals(false);
}


void ProcessingWindow::buttonClick() {
  emit buttonClicked(MODE::CLOSE);
}

// private methods ============================================================

void ProcessingWindow::initUi() {
  ui->setupUi(this);

  ui->messageLabel->setFont(settings->getFont("Liberation Sans", "Bold", 20));
  ui->exitButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));

  connect(ui->exitButton, SIGNAL(released()), this, SLOT(buttonClick()));
}
