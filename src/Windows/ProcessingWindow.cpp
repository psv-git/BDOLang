#include "ProcessingWindow.hpp"
#include "ui_ProcessingWindow.h"
#include "DataHandler.hpp"


ProcessingWindow::ProcessingWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ProcessingWindow) {
  ui->setupUi(this);

  ui->okButton->setFont(GetFont("Liberation Sans",      "Bold",    12));
  ui->messageLabel->setFont(GetFont("Liberation Sans",  "Bold",    20));

  connect(ui->okButton, &QPushButton::released, this, &ProcessingWindow::onButtonClick);
}


ProcessingWindow::~ProcessingWindow() {
  delete ui;
}

// public slots ===============================================================

void ProcessingWindow::show(MODE mode, const QString &srcFilePath, const QString &targFilePath) {
  isError = false;
  ui->okButton->setEnabled(false);
  ui->messageLabel->setText("PROCESSING");
  QWidget::show();

  Delay(100); // TODO: to thread
  if (mode == MODE::BIN_TO_TEXT) {
    try { DataHandler::getInstance().convertBinFileToTextFile(srcFilePath, targFilePath); }
    catch (...) { isError = true; }
  } else if (mode == MODE::TEXT_TO_BIN) {
    try { DataHandler::getInstance().convertTextFileToBinFile(srcFilePath, targFilePath); }
    catch (...) { isError = true; }
  }

  if (isError) {
    QErrorMessage::qtHandler()->showMessage(GetExceptionsMessage());
    ui->messageLabel->setText("FAIL");
  } else {
    ui->okButton->setEnabled(true);
    ui->messageLabel->setText("DONE");
  }
}

// private slots ==============================================================

void ProcessingWindow::onButtonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "okButton") {
    emit buttonClicked(MODE::CLOSE);
  }
}
