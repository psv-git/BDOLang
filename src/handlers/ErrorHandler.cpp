#include "ErrorHandler.hpp"
#include "ui_ErrorWindow.h"


ErrorHandler::ErrorHandler(QWidget *parent) : QWidget(parent), m_ui(new Ui::ErrorWindow) {
  m_ui->setupUi(this);

  connect(m_ui->okButton, SIGNAL(released()), this, SLOT(buttonClick()));
}


ErrorHandler::~ErrorHandler() {
  delete m_ui;
}

// public slots ===============================================================

void ErrorHandler::showMessage() {
  QString errorMessage;
  for (int i = 0; i < m_errorsMessagesList.size(); i++) {
    errorMessage += m_errorsMessagesList.at(i) + "\n";
  }
  m_errorsMessagesList.clear();
  m_ui->errorEdit->appendPlainText(errorMessage);
  this->show();
}

// public methods =============================================================

void ErrorHandler::addErrorMessage(const QString &errorMessage) {
  m_errorsMessagesList.push_back(errorMessage);
}

// private slots ==============================================================

void ErrorHandler::buttonClick() {
  m_ui->errorEdit->clear();
  this->hide();
}
