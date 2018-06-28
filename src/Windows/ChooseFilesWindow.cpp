#include "ChooseFilesWindow.hpp"
#include "ui_ChooseFilesWindow.h"


ChooseFilesWindow::ChooseFilesWindow(QWidget *parent) : QWidget(parent), ui(new Ui::ChooseFilesWindow) {
  ui->setupUi(this);
  settings = &Settings::getInstance();

  ui->okButton->setFont(settings->getFont("Liberation Sans",         "Bold",    12));
  ui->cancelButton->setFont(settings->getFont("Liberation Sans",     "Bold",    12));
  ui->sourcePathButton->setFont(settings->getFont("Liberation Sans", "Bold",    12));
  ui->targetPathButton->setFont(settings->getFont("Liberation Sans", "Bold",    12));
  ui->sourcePathEdit->setFont(settings->getFont("Liberation Mono",   "Regular", 10));
  ui->targetPathEdit->setFont(settings->getFont("Liberation Mono",   "Regular", 10));
  ui->sourcePathLabel->setFont(settings->getFont("Liberation Sans",  "Bold",    11));
  ui->targetPathLabel->setFont(settings->getFont("Liberation Sans",  "Bold",    11));

  connect(ui->okButton,         SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton,     SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->sourcePathButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->targetPathButton, SIGNAL(released()), this, SLOT(buttonClick()));
}


ChooseFilesWindow::~ChooseFilesWindow() {
  delete ui;
}

// public slots ===============================================================

void ChooseFilesWindow::show(MODE mode) {
//  QString dataPath = settings->getSetting("path/data_directory", DEFAULT_SETTINGS.dataDirectoryName).toString();

//  if (mode == MODE::BIN_TO_TEXT) {
//    ui->sourcePathEdit->setText(dataPath + "/" + settings->getSetting("path/source_loc_name", DEFAULT_SETTINGS.sourceLocFileName).toString());
//    ui->targetPathEdit->setText(dataPath + "/" + settings->getSetting("path/source_text_name", DEFAULT_SETTINGS.sourceTextFileName).toString());
//  }

//  if (mode == MODE::TEXT_TO_BIN) {
//    ui->sourcePathEdit->setText(dataPath + "/" + settings->getSetting("path/source_text_name", DEFAULT_SETTINGS.sourceTextFileName).toString());
//    ui->targetPathEdit->setText(dataPath + "/" + settings->getSetting("path/source_loc_name", DEFAULT_SETTINGS.sourceLocFileName).toString());
//  }

//  if (mode == MODE::MERGE_BIN) {
//    ui->sourcePathEdit->setText(dataPath + "/" + settings->getSetting("path/target_loc_name", DEFAULT_SETTINGS.targetLocFileName).toString());
//    ui->targetPathEdit->setText(dataPath + "/" + settings->getSetting("path/source_loc_name", DEFAULT_SETTINGS.sourceLocFileName).toString());
//  }

//  if (mode == MODE::MERGE_TEXT) {
//    ui->sourcePathEdit->setText(dataPath + "/" + settings->getSetting("path/target_text_name", DEFAULT_SETTINGS.targetTextFileName).toString());
//    ui->targetPathEdit->setText(dataPath + "/" + settings->getSetting("path/source_text_name", DEFAULT_SETTINGS.sourceTextFileName).toString());
//  }

  QWidget::show();
}

// private slots ==============================================================

void ChooseFilesWindow::buttonClick () {
  QObject* obj = QObject::sender();
  QString objName = obj->objectName();
//  if (objName == "okButton") {
//    QString srcFilePath(ui->sourcePathEdit->text());
//    QString targFilePath(ui->targetPathEdit->text());
//    QString dataPath = settings->getSetting("path/data_directory", DEFAULT_SETTINGS.dataDirectoryName).toString();
//    if (srcFilePath.isEmpty()) srcFilePath = dataPath + settings->getSetting("path/source_loc_name",  DEFAULT_SETTINGS.sourceLocFileName).toString();
//    if (targFilePath.isEmpty()) targFilePath = dataPath + settings->getSetting("path/target_loc_name",  DEFAULT_SETTINGS.targetLocFileName).toString();
//    emit buttonClicked(srcFilePath, targFilePath);
//  } else if (objName == "cancelButton") {
//    emit buttonClicked(MODE::CLOSE);
//  } else if (objName == "sourcePathButton") {
//    ui->sourcePathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
//  } else if (objName == "targetPathButton") {
//    ui->targetPathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
//  }
}
