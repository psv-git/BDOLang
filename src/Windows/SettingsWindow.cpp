#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "CustomComboBox.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
  ui->setupUi(this);
  settings = &Settings::getInstance();

  ui->saveButton->setFont(GetFont("Liberation Sans",         "Bold",    12));
  ui->cancelButton->setFont(GetFont("Liberation Sans",       "Bold",    12));
  ui->chooseButton1->setFont(GetFont("Liberation Sans",      "Bold",    12));
  ui->chooseButton2->setFont(GetFont("Liberation Sans",      "Bold",    12));
  ui->chooseButton3->setFont(GetFont("Liberation Sans",      "Bold",    12));
  ui->languageBox->setFont(GetFont("Liberation Sans",        "Bold",    12));
  ui->compressingBox->setFont(GetFont("Liberation Sans",     "Bold",    12));
  ui->dataDirectoryEdit->setFont(GetFont("Liberation Mono",  "Regular", 10));
  ui->sourceNameEdit->setFont(GetFont("Liberation Mono",     "Regular", 10));
  ui->targetNameEdit->setFont(GetFont("Liberation Mono",     "Regular", 10));
  ui->dataDirectoryLabel->setFont(GetFont("Liberation Sans", "Bold",    11));
  ui->sourceNameLabel->setFont(GetFont("Liberation Sans",    "Bold",    11));
  ui->targetNameLabel->setFont(GetFont("Liberation Sans",    "Bold",    11));
  ui->languageLabel->setFont(GetFont("Liberation Sans",      "Bold",    11));
  ui->aboutEdit->setFont(GetFont("Liberation Sans",          "Bold",    10));

  connect(ui->saveButton,    SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton,  SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->chooseButton1, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->chooseButton2, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->chooseButton3, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->chooseButton4, SIGNAL(released()), this, SLOT(buttonClick()));
}


SettingsWindow::~SettingsWindow() {
  delete ui;
}

// public slots ===============================================================

void SettingsWindow::show() {
  ui->languageBox->setCurrentValue(settings->getSetting("language/language", DEFAULT_SETTINGS.language).toInt());
  ui->compressingBox->setCurrentValue(settings->getSetting("compressing/compressing_level", DEFAULT_SETTINGS.compressingLevel).toInt());
  ui->dataDirectoryEdit->setText(settings->getSetting("path/data_path", DEFAULT_SETTINGS.dataPath).toString());
  ui->sourceNameEdit->setText(settings->getSetting("path/source_name", DEFAULT_SETTINGS.sourceFileName).toString());
  ui->targetNameEdit->setText(settings->getSetting("path/target_name", DEFAULT_SETTINGS.targetFileName).toString());
  ui->textNameEdit->setText(settings->getSetting("path/text_name", DEFAULT_SETTINGS.textFileName).toString());
  QWidget::show();
}

// private slots ==============================================================

void SettingsWindow::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "chooseButton1")      ui->dataDirectoryEdit->setText(GetDirectoryPath(tr("Choose directory")));
  else if (objName == "chooseButton2") ui->sourceNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
  else if (objName == "chooseButton3") ui->targetNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
  else if (objName == "chooseButton4") ui->textNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
  else if (objName == "saveButton") {
    // save language
    settings->setSetting("language/language", ui->languageBox->getCurrentValue(), false);
    // save compressing
    settings->setSetting("compressing/compressing_level", ui->compressingBox->getCurrentValue(), false);
    // save data path
    QString tmp = ui->dataDirectoryEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataPath;
    if (tmp.back() != '/') tmp.append('/');
    settings->setSetting("path/data_path", tmp, false);
    // save source file name
    tmp = ui->sourceNameEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.sourceFileName;
    settings->setSetting("path/source_name", tmp, false);
    // save target file name
    tmp = ui->targetNameEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.targetFileName;
    settings->setSetting("path/target_name", tmp, false);
    // save text file name
    tmp = ui->textNameEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.targetFileName;
    settings->setSetting("path/text_name", tmp, true);
    emit buttonClicked(MODE::CLOSE);
  } else if (objName == "cancelButton") {
    emit buttonClicked(MODE::CLOSE);
  }
}
