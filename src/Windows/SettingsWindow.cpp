#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "LanguageComboBox.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
  ui->setupUi(this);
  connect(ui->saveButton,    &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->cancelButton,  &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->chooseButton1, &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->chooseButton2, &QPushButton::released, this, &SettingsWindow::onButtonClick);
  connect(ui->chooseButton3, &QPushButton::released, this, &SettingsWindow::onButtonClick);
}


SettingsWindow::~SettingsWindow() {
  delete ui;
}

// public slots ===============================================================

void SettingsWindow::show() {
  ui->languageBox->setCurrentLanguage(active_settings.language);
  ui->dataPathEdit->setText(active_settings.dataPath);
  ui->fileNameEdit1->setText(active_settings.sourceFileName);
  ui->fileNameEdit2->setText(active_settings.targetFileName);
  QWidget::show();
}

// private slots ==============================================================

void SettingsWindow::onButtonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "chooseButton1")      ui->dataPathEdit->setText(GetDirectoryPath(tr("Choose directory")));
  else if (objName == "chooseButton2") ui->fileNameEdit1->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
  else if (objName == "chooseButton3") ui->fileNameEdit2->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
  else if (objName == "saveButton") {
    active_settings.language = ui->languageBox->getCurrentLanguage();
    QString tmp = ui->dataPathEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataPath;
    if (tmp.back() != '/') tmp.append('/');
    active_settings.dataPath = tmp;
    tmp = ui->fileNameEdit1->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.sourceFileName;
    active_settings.sourceFileName = tmp;
    tmp = ui->fileNameEdit2->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.targetFileName;
    active_settings.targetFileName = tmp;
    if (!WriteConfigFile(active_settings)) {
      SetDefaultSettings();
      QErrorMessage::qtHandler()->showMessage("Write new setiings to config file was failed. Returning to default settings.");
    }
    emit buttonClicked(MODE::CLOSE);
  } else if (objName == "cancelButton") {
    emit buttonClicked(MODE::CLOSE);
  }
}
