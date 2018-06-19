#include "ChooseFilesWindow.hpp"
#include "ui_ChooseFilesWindow.h"
#include "WindowsHandler.hpp"
#include "ApplicationFunctions.hpp"


ChooseFilesWindow::ChooseFilesWindow(WindowsHandler *parent) : ui(new Ui::ChooseFilesWindow) {
  ChooseFilesWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->okButton, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->cancelButton, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton1, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton2, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
}


ChooseFilesWindow::~ChooseFilesWindow() {
  delete ui;
}


void ChooseFilesWindow::show() {
  ui->pathEdit1->setText(active_settings.dataPath + active_settings.sourceFileName);
  ui->pathEdit2->setText(active_settings.dataPath + active_settings.targetFileName);
  QWidget::show();
}

// ===========================================================================

void ChooseFilesWindow::onButtonClick () {
  QObject* obj = sender();
  QString objName = obj->objectName();
  if (objName == "okButton") {
    QString srcFilePath(ui->pathEdit1->text());
    QString targFilePath(ui->pathEdit2->text());
    if (srcFilePath.isEmpty()) srcFilePath = active_settings.dataPath + active_settings.sourceFileName;
    if (targFilePath.isEmpty()) targFilePath = active_settings.dataPath + active_settings.targetFileName;
    parent->onButtonClick(this, srcFilePath, targFilePath);
  }
  if (objName == "cancelButton") {
    parent->onButtonClick(this, MODE::CLOSE);
  }
  if (objName == "chooseButton1") {
    ui->pathEdit1->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  }
  if (objName == "chooseButton2") {
    ui->pathEdit2->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  }
}
