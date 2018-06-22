#include "ProcessingWindow.hpp"
#include "ui_ProcessingWindow.h"
#include "WindowsHandler.hpp"
#include "DataHandler.hpp"


ProcessingWindow::ProcessingWindow(WindowsHandler *parent) : ui(new Ui::ProcessingWindow) {
  ProcessingWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->okButton, &QPushButton::released, this, &ProcessingWindow::onButtonClick);
}


ProcessingWindow::~ProcessingWindow() {
  delete ui;
}

// ============================================================================

void ProcessingWindow::show(MODE mode, const QString &srcFilePath, const QString &targFilePath) {
  isError = false;
  ui->messageLabel->setText("PROCESSING");
  QWidget::show();
  Delay(100);
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
    ui->messageLabel->setText("DONE");
  }
}

// ============================================================================

void ProcessingWindow::onButtonClick() {
  QObject *obj = sender();
  QString objName = obj->objectName();
  if (objName == "okButton") parent->onButtonClick(this, MODE::CLOSE);
}
