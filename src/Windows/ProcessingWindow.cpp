#include <QThread>
#include <QTimer>
#include "ProcessingWindow.hpp"
#include "ui_ProcessingWindow.h"
#include "DataHandler.hpp"


ProcessingWindow::ProcessingWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ProcessingWindow) {
  settingsHandler = &SettingsHandler::getInstance();
  errorHandler = &ErrorHandler::getInstance();
  initUi();
}


ProcessingWindow::~ProcessingWindow() {
  delete ui;
}

// events =====================================================================

bool ProcessingWindow::event(QEvent *event) {
  if (event->type() == QEvent::Close) {
    emit buttonClicked(MODE::CLOSE);
  }
  return QWidget::event(event);
}

// public slots ===============================================================

void ProcessingWindow::show(const QString &srcFilePath, const QString &targFilePath, MODE mode) {
//  this->blockSignals(true);
  ui->exitButton->setEnabled(false);
  ui->messageLabel->setText("PROCESSING");
  QWidget::show();

  // work on another thread
//  QThread *thread = new QThread();
//  QTimer *timer = new QTimer();
  DataHandler *dataHandler = new DataHandler(srcFilePath, targFilePath, mode);

  connect(dataHandler, SIGNAL(progressed(int)), ui->progressBar, SLOT(setValue(int)));
  connect(dataHandler, SIGNAL(completed()), this, SLOT(complete()));
  connect(dataHandler, SIGNAL(failed()), this, SLOT(error()));

  dataHandler->run();

//  timer->setInterval(1000);

//  connect(dataHandler, SIGNAL(progressed(int)), ui->progressBar, SLOT(setValue(int)));
//  connect(dataHandler, SIGNAL(failed()), this, SLOT(error()));
//  connect(dataHandler, SIGNAL(failed()), thread, SLOT(quit()));
//  connect(dataHandler, SIGNAL(completed()), this, SLOT(complete()));
//  connect(dataHandler, SIGNAL(completed()), thread, SLOT(quit()));

//  connect(thread, SIGNAL(started()), timer, SLOT(start()));
//  connect(thread, SIGNAL(finished()), timer, SLOT(deleteLater()));
//  connect(thread, SIGNAL(finished()), dataHandler, SLOT(deleteLater()));

//  connect(timer, SIGNAL(timeout()), dataHandler, SLOT(test()));

//  dataHandler->moveToThread(thread);
//  timer->moveToThread(thread);

//  thread->start();

}

// private slots ==============================================================

void ProcessingWindow::complete() {
  ui->exitButton->setEnabled(true);
  ui->messageLabel->setText("DONE");
//  this->blockSignals(false);
}


void ProcessingWindow::error() {
  errorHandler->showMessage();
}


void ProcessingWindow::buttonClick() {
  emit buttonClicked(MODE::CLOSE);
}

// private methods ============================================================

void ProcessingWindow::initUi() {
  ui->setupUi(this);

  ui->messageLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 20));
  ui->exitButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(ui->exitButton, SIGNAL(released()), this, SLOT(buttonClick()));
}
