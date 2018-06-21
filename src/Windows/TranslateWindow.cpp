#include "TranslateWindow.hpp"
#include "ui_TranslateWindow.h"
#include "WindowsHandler.hpp"
#include "DataHandler.hpp"


TranslateWindow::TranslateWindow(WindowsHandler *parent) : ui(new Ui::TranslateWindow) {
  TranslateWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->prevButton, &QPushButton::released, this, &TranslateWindow::onButtonClick);
  connect(ui->nextButton, &QPushButton::released, this, &TranslateWindow::onButtonClick);
  connect(ui->saveButton, &QPushButton::released, this, &TranslateWindow::onButtonClick);
  connect(ui->cancelButton, &QPushButton::released, this, &TranslateWindow::onButtonClick);
}


TranslateWindow::~TranslateWindow() {
  delete ui;
}


void TranslateWindow::show(const QString &inFilePath, const QString &outFilePath) {
  isError = false;
//  std::string path = inFileName.toStdString();
//  std::ifstream input;
//  try {
//    openInputFile(input, path, "TranslateWindow::show()");
//    DataHandler::getInstance().readDataFromBinFile(input);
//    closeFile(input, path, "TranslateWindow::show()");
//  }
//  catch (const std::exception &e) {
//    isError = true;
//    if (input.is_open()) closeFile(input, path, "TranslateWindow::show()");
//    std::cerr << e.what() << std::endl;
//    QErrorMessage::qtHandler()->showMessage(QString(e.what()));
//  }
  QWidget::show();
}


void TranslateWindow::hide() {
  QWidget::hide();
}

// ===========================================================================

void TranslateWindow::onButtonClick () {
  QObject *obj = sender();
  QString objName = obj->objectName();
  if (objName == "saveButton") {
    if (isError) parent->onButtonClick(this, MODE::CLOSE);
    if (!isError) parent->onButtonClick(this, MODE::CLOSE);
  }
  if (objName == "cancelButton") parent->onButtonClick(this, MODE::CLOSE);
}
