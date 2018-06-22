#include "ChooseFileWindow.hpp"
#include "ui_ChooseFileWindow.h"


ChooseFileWindow::ChooseFileWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ChooseFileWindow) {
  ui->setupUi(this);
  connect(ui->okButton,     &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->cancelButton, &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->chooseButton, &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
}


ChooseFileWindow::~ChooseFileWindow() {
  delete ui;
}

// public slots ===============================================================

void ChooseFileWindow::show() {
  ui->pathEdit->setText(active_settings.dataPath + active_settings.sourceFileName);
  QWidget::show();
}

// private slots ==============================================================

void ChooseFileWindow::onButtonClick () {
  QObject* obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "okButton") {
    QString srcFilePath(ui->pathEdit->text());
    if (srcFilePath.isEmpty()) srcFilePath = active_settings.dataPath + active_settings.sourceFileName;
    emit buttonClicked(srcFilePath, "");
  } else if (objName == "cancelButton") {
    emit buttonClicked(MODE::CLOSE);
  } else if (objName == "chooseButton") {
    ui->pathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  }
}
