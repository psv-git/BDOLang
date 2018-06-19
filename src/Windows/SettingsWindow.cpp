#include <QErrorMessage>
#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "WindowsHandler.hpp"
#include "ApplicationFunctions.hpp"
#include "LanguageComboBox.hpp"


SettingsWindow::SettingsWindow(WindowsHandler *parent) : ui(new Ui::SettingsWindow) {
  SettingsWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->saveButton, &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->cancelButton, &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->chooseButton1, &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->chooseButton2, &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->chooseButton3, &QPushButton::released, this, &SettingsWindow::onButtonClick);
}


SettingsWindow::~SettingsWindow() {
  delete ui;
}


void SettingsWindow::show() {
  ui->languageBox->setCurrentLanguage(active_settings.language);
  ui->dataPathEdit->setText(active_settings.dataPath);
  ui->fileNameEdit1->setText(active_settings.sourceFileName);
  ui->fileNameEdit2->setText(active_settings.targetFileName);
  QWidget::show();
}

// ===========================================================================

void SettingsWindow::onButtonClick() {
  QObject *obj = sender();
  QString objName = obj->objectName();
  if (objName == "saveButton") {
    active_settings.language = ui->languageBox->getCurrentLanguage();
    active_settings.dataPath = ui->dataPathEdit->text();
    active_settings.sourceFileName = ui->fileNameEdit1->text();
    active_settings.targetFileName = ui->fileNameEdit2->text();
    if (!WriteConfigFile(active_settings)) {
      SetDefaultSettings();
      QErrorMessage::qtHandler()->showMessage("Write new setiings to config file was failed. Returning to default settings.");
    }
    parent->onButtonClick(this, MODE::CLOSE);
  }
  if (objName == "cancelButton") parent->onButtonClick(this, MODE::CLOSE);
  if (objName == "chooseButton1") ui->dataPathEdit->setText(GetDirectoryPath(tr("Choose directory")));
  if (objName == "chooseButton2") ui->fileNameEdit1->setText(GetFileName(tr("Choose file"),  tr("Files extensions (*)")));
  if (objName == "chooseButton3") ui->fileNameEdit2->setText(GetFileName(tr("Choose file"),  tr("Files extensions (*)")));
}
