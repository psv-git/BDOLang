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
  QString exceptionMessage;
  for (int i = exceptionsMessagesList.size(); i > 0; i--) {
    exceptionMessage = exceptionMessage + QString::number(i) + ") " + exceptionsMessagesList.at(i - 1) + "\n";
  }
  exceptionsMessagesList.clear();
  ui->errorEdit->appendPlainText(exceptionMessage);
  this->show();
}

// public methods =============================================================

void ErrorHandler::addException(const QString &exceptionMessage) {
  exceptionsMessagesList.push_back(exceptionMessage);
}

// private slots ==============================================================

void ErrorHandler::buttonClick() {
  ui->errorEdit->clear();
  this->hide();
}
