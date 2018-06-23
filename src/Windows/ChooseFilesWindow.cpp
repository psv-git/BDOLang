#include "ChooseFilesWindow.hpp"
#include "ui_ChooseFilesWindow.h"


ChooseFilesWindow::ChooseFilesWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ChooseFilesWindow) {
  ui->setupUi(this);

  ui->okButton->setFont(GetFont("Liberation Sans",      "Bold",    12));
  ui->cancelButton->setFont(GetFont("Liberation Sans",  "Bold",    12));
  ui->chooseButton1->setFont(GetFont("Liberation Sans", "Bold",    12));
  ui->chooseButton2->setFont(GetFont("Liberation Sans", "Bold",    12));
  ui->pathEdit1->setFont(GetFont("Liberation Mono",     "Regular", 10));
  ui->pathEdit2->setFont(GetFont("Liberation Mono",     "Regular", 10));
  ui->pathLabel1->setFont(GetFont("Liberation Sans",    "Bold",    11));
  ui->pathLabel2->setFont(GetFont("Liberation Sans",    "Bold",    11));

  connect(ui->okButton,      &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->cancelButton,  &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton1, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton2, &QPushButton::released, this, &ChooseFilesWindow::onButtonClick);

  settings = &Settings::getInstance();
}


ChooseFilesWindow::~ChooseFilesWindow() {
  delete ui;
}

// public slots ===============================================================

void ChooseFilesWindow::show() {
  QString dataPath = settings->getSetting("path/data_path", DEFAULT_SETTINGS.dataPath).toString();
  ui->pathEdit1->setText(dataPath + settings->getSetting("path/source_name",  DEFAULT_SETTINGS.sourceFileName).toString());
  ui->pathEdit2->setText(dataPath + settings->getSetting("path/target_name",  DEFAULT_SETTINGS.targetFileName).toString());
  QWidget::show();
}

// private slots ==============================================================

void ChooseFilesWindow::onButtonClick () {
  QObject* obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "okButton") {
    QString srcFilePath(ui->pathEdit1->text());
    QString targFilePath(ui->pathEdit2->text());
    QString dataPath = settings->getSetting("path/data_path", DEFAULT_SETTINGS.dataPath).toString();
    if (srcFilePath.isEmpty()) srcFilePath = dataPath + settings->getSetting("path/source_name",  DEFAULT_SETTINGS.sourceFileName).toString();
    if (targFilePath.isEmpty()) targFilePath = dataPath + settings->getSetting("path/target_name",  DEFAULT_SETTINGS.targetFileName).toString();
    emit buttonClicked(srcFilePath, targFilePath);
  } else if (objName == "cancelButton") {
    emit buttonClicked(MODE::CLOSE);
  } else if (objName == "chooseButton1") {
    ui->pathEdit1->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  } else if (objName == "chooseButton2") {
    ui->pathEdit2->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
  }
}
