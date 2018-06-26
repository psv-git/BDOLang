#include "TranslatingWindow.hpp"
#include "ui_TranslatingWindow.h"
#include "DataHandler.hpp"


TranslatingWindow::TranslatingWindow(QWidget *parent) : QWidget(parent), ui(new Ui::TranslatingWindow) {
  ui->setupUi(this);

  // TODO: fonts

  connect(ui->prevButton,   SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->nextButton,   SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->saveButton,   SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
}


TranslatingWindow::~TranslatingWindow() {
  delete ui;
}

// public slots ===============================================================

void TranslatingWindow::show(const QString &inFilePath, const QString &outFilePath) {
//  std::string path = inFileName.toStdString();
//  std::ifstream input;
//  try {
//    openInputFile(input, path, "TranslatingWindow::show()");
//    DataHandler::getInstance().readDataFromBinFile(input);
//    closeFile(input, path, "TranslatingWindow::show()");
//  }
//  catch (const std::exception &e) {
//    isError = true;
//    if (input.is_open()) closeFile(input, path, "TranslatingWindow::show()");
//    std::cerr << e.what() << std::endl;
//    QErrorMessage::qtHandler()->showMessage(QString(e.what()));
//  }
  QWidget::show();
}


void TranslatingWindow::hide() {
  QWidget::hide();
}

// private slots ==============================================================

void TranslatingWindow::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "saveButton") {
    emit buttonClicked(MODE::CLOSE);
  } else if (objName == "cancelButton") {
    emit buttonClicked(MODE::CLOSE);
  }
}
