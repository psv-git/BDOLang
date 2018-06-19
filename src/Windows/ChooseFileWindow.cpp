#include "ChooseFileWindow.hpp"
#include "ui_ChooseFileWindow.h"
#include "WindowsHandler.hpp"
#include "ApplicationFunctions.hpp"


ChooseFileWindow::ChooseFileWindow(WindowsHandler *parent) : ui(new Ui::ChooseFileWindow) {
  ChooseFileWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->okButton, &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->cancelButton, &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->chooseButton, &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
}


ChooseFileWindow::~ChooseFileWindow() {
  delete ui;
}


void ChooseFileWindow::show() {
  ui->pathEdit->setText(active_settings.dataPath + active_settings.sourceFileName);
  QWidget::show();
}

// ===========================================================================

void ChooseFileWindow::onButtonClick () {
  QObject* obj = sender();
  QString objName = obj->objectName();
  if (objName == "okButton") {
    QString srcFilePath(ui->pathEdit->text());
    if (srcFilePath.isEmpty()) srcFilePath = active_settings.dataPath + active_settings.sourceFileName;
    parent->onButtonClick(this, srcFilePath, "");
  }
  if (objName == "cancelButton") {
    parent->onButtonClick(this, MODE::CLOSE);
  }
  if (objName == "chooseButton") {
    ui->pathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  }
}
