#include "ChooseFileWindow.hpp"
#include "ui_ChooseFileWindow.h"


ChooseFileWindow::ChooseFileWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ChooseFileWindow) {
  ui->setupUi(this);

  ui->okButton->setFont(GetFont("Liberation Sans",     "Bold",    12));
  ui->cancelButton->setFont(GetFont("Liberation Sans", "Bold",    12));
  ui->chooseButton->setFont(GetFont("Liberation Sans", "Bold",    12));
  ui->pathEdit->setFont(GetFont("Liberation Mono",     "Regular", 10));
  ui->pathLabel->setFont(GetFont("Liberation Sans",    "Bold",    11));

  connect(ui->okButton,     &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->cancelButton, &QPushButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->chooseButton, &QPushButton::released, this, &ChooseFileWindow::onButtonClick);

  settings = &Settings::getInstance();
}


ChooseFileWindow::~ChooseFileWindow() {
  delete ui;
}

// public slots ===============================================================

void ChooseFileWindow::show() {
  ui->pathEdit->setText(settings->getSetting("path/data_path", DEFAULT_SETTINGS.dataPath).toString() + settings->getSetting("path/source_name",  DEFAULT_SETTINGS.sourceFileName).toString());
  QWidget::show();
}

// private slots ==============================================================

void ChooseFileWindow::onButtonClick () {
  QObject* obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "okButton") {
    QString srcFilePath(ui->pathEdit->text());
    if (srcFilePath.isEmpty()) srcFilePath = settings->getSetting("path/data_path", DEFAULT_SETTINGS.dataPath).toString() + settings->getSetting("path/source_name",  DEFAULT_SETTINGS.sourceFileName).toString();
    emit buttonClicked(srcFilePath, "");
  } else if (objName == "cancelButton") {
    emit buttonClicked(MODE::CLOSE);
  } else if (objName == "chooseButton") {
    ui->pathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  }
}
