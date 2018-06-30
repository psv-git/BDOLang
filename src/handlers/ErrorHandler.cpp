#include "ErrorHandler.hpp"
#include "ui_ErrorWindow.h"


ErrorHandler::ErrorHandler(QWidget *parent) : QWidget(parent), ui(new Ui::ErrorWindow) {
  ui->setupUi(this);

  connect(ui->okButton, SIGNAL(released()), this, SLOT(buttonClick()));
}


ErrorHandler::~ErrorHandler() {
  delete ui;
}

// public slots ===============================================================

void ErrorHandler::showMessage() {
  QString errorMessage;
  for (int i = errorsMessagesList.size(); i > 0; i--) {
    errorMessage = errorMessage + QString::number(i) + ") " + errorsMessagesList.at(i - 1) + "\n";
  }
  errorsMessagesList.clear();
  ui->errorEdit->appendPlainText(errorMessage);
  this->show();
}

// public methods =============================================================

void ErrorHandler::addErrorMessage(const QString &errorMessage) {
  errorsMessagesList.push_back(errorMessage);
}

// private slots ==============================================================

void ErrorHandler::buttonClick() {
  ui->errorEdit->clear();
  this->hide();
}
