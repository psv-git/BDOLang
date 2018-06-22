#include "ChooseFilesWindow.hpp"
#include "ui_ChooseFilesWindow.h"


ChooseFilesWindow::ChooseFilesWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ChooseFilesWindow) {
  ui->setupUi(this);
  connect(ui->okButton,      &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->cancelButton,  &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton1, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton2, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
}


ChooseFilesWindow::~ChooseFilesWindow() {
  delete ui;
}

// public slots ===============================================================

void ChooseFilesWindow::show() {
  ui->pathEdit1->setText(active_settings.dataPath + active_settings.sourceFileName);
  ui->pathEdit2->setText(active_settings.dataPath + active_settings.targetFileName);
  QWidget::show();
}

// private slots ==============================================================

void ChooseFilesWindow::onButtonClick () {
  QObject* obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "okButton") {
    QString srcFilePath(ui->pathEdit1->text());
    QString targFilePath(ui->pathEdit2->text());
    if (srcFilePath.isEmpty()) srcFilePath = active_settings.dataPath + active_settings.sourceFileName;
    if (targFilePath.isEmpty()) targFilePath = active_settings.dataPath + active_settings.targetFileName;
    emit buttonClicked(srcFilePath, targFilePath);
  } else if (objName == "cancelButton") {
    emit buttonClicked(MODE::CLOSE);
  } else if (objName == "chooseButton1") {
    ui->pathEdit1->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  } else if (objName == "chooseButton2") {
    ui->pathEdit2->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  }
}
