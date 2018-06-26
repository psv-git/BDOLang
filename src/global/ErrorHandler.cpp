#include <QErrorMessage>
#include "ErrorHandler.hpp"


ErrorHandler::ErrorHandler() {
  QErrorMessage::qtHandler()->setModal(true);
}


ErrorHandler::~ErrorHandler() {}

// public methods =============================================================

void ErrorHandler::addException(const QString &exceptionMessage) {
  exceptionsMessagesList.push_back(exceptionMessage);
}


void ErrorHandler::showMessage() {
  QString exceptionMessage;
  for (int i = 0; i < exceptionsMessagesList.size(); i++) {
    exceptionMessage += exceptionsMessagesList.at(i);
    exceptionMessage.push_back('\n');
  }
  exceptionsMessagesList.clear();
  QErrorMessage::qtHandler()->showMessage(exceptionMessage);
}
