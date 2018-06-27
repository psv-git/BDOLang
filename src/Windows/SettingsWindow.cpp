#include <QFormLayout>
#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "CustomComboBox.hpp"
#include "LanguageWidget.hpp"
#include "LanguageHandler.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
  ui->setupUi(this);
  settings = &Settings::getInstance();
  LanguageHandler::getInstance().setHandledObjects(languageWidgetsList);

  ui->saveButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->cancelButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->compressingBox->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->compressingLabel->setFont(settings->getFont("Liberation Sans", "Bold", 11));
  ui->aboutEdit->setFont(settings->getFont("Liberation Sans", "Bold", 10));

  connect(ui->saveButton,   SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->addButton,    SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->deleteButton, SIGNAL(released()), this, SLOT(buttonClick()));
}


SettingsWindow::~SettingsWindow() {
  delete ui;
  for (int i = 0; i < languageWidgetsList.size(); i++) {
    if (!languageWidgetsList.at(i)) delete languageWidgetsList[i];
  }
}

// public slots ===============================================================

void SettingsWindow::show() {
  ui->compressingBox->setValue(settings->getSetting("compressing/compressing_level", DEFAULT_SETTINGS.compressingLevel).toInt());
  QWidget::show();
}

// private slots ==============================================================

void SettingsWindow::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "cancelButton")      emit buttonClicked(MODE::CLOSE);
  else if (objName == "addButton")    addLanguageWidget(true, LANG::EMPTY, "", "");
  else if (objName == "deleteButton") deleteLanguageWidgets();
//  if (objName == "dataDirectoryButton")       ui->dataDirectoryEdit->setText(GetDirectoryPath(tr("Choose directory")));
//  else if (objName == "sourceLocNameButton")  ui->sourceLocNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
//  else if (objName == "targetLocNameButton")  ui->targetLocNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
//  else if (objName == "sourceTextNameButton") ui->sourceTextNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
//  else if (objName == "targetTextNameButton") ui->sourceTextNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
//  if (objName == "saveButton") {
//    // save language
//    settings->setSetting("language/language", ui->languageBox->getValue());
//    // save compressing
//    settings->setSetting("compressing/compressing_level", ui->compressingBox->getValue());
//    // save data path
//    QString tmp = ui->dataDirectoryEdit->text();
//    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataDirectoryName;
////    if (tmp.back() != '/') tmp.append('/');
//    settings->setSetting("path/data_directory", tmp);
//    // save source file name
//    tmp = ui->sourceLocNameEdit->text();
//    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.sourceLocFileName;
//    settings->setSetting("path/source_loc_name", tmp);
//    // save target file name
//    tmp = ui->targetLocNameEdit->text();
//    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.targetLocFileName;
//    settings->setSetting("path/target_loc_name", tmp);
//    // save source text file name
//    tmp = ui->sourceTextNameEdit->text();
//    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.sourceTextFileName;
//    settings->setSetting("path/source_text_name", tmp);
//    // save source text file name
//    tmp = ui->sourceTextNameEdit->text();
//    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.targetTextFileName;
//    settings->setSetting("path/target_text_name", tmp);
//    settings->saveSettings();
//    emit buttonClicked(MODE::CLOSE);
//  } else if (objName == "cancelButton") {
//    emit buttonClicked(MODE::CLOSE);
//  }
}

// private methods ============================================================

void SettingsWindow::addLanguageWidget(bool deletable, LANG language, const QString &locFileName, const QString &textFileName) {
  LanguageWidget *lw = new LanguageWidget();
  languageWidgetsList.push_back(lw);
  lw->setDeletable(deletable);
  lw->setLanguage(language);
  lw->setLocFileName(locFileName);
  lw->setTextFileName(textFileName);
  ui->scrollAreaContents->layout()->addWidget(lw);
}


void SettingsWindow::deleteLanguageWidgets() {
  for (auto it = languageWidgetsList.begin(); it != languageWidgetsList.end();) {
    if ((*it)->needToDelete()) {
      ui->scrollAreaContents->layout()->removeWidget(*it);
      delete *it;
      it = languageWidgetsList.erase(it);
    } else it++;
  }
}


