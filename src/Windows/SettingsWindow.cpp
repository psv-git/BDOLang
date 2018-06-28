#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "CustomComboBox.hpp"
#include "LanguageWidget.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
  ui->setupUi(this);
  settings = &Settings::getInstance();
  LanguageHandler::getInstance().setHandledObject(this);

  ui->saveButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->cancelButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->compressingBox->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->compressingLabel->setFont(settings->getFont("Liberation Sans", "Bold", 11));
  ui->aboutEdit->setFont(settings->getFont("Liberation Sans", "Bold", 10));

  connect(ui->saveButton,     SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton,   SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->addButton,      SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->deleteButton,   SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->dataPathButton, SIGNAL(released()), this, SLOT(buttonClick()));

  addLanguageWidget(false, LANG::EN, "languagedata_en.loc", "languagedata_en.txt");
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

// public methods =============================================================

void SettingsWindow::updateLanguage() {
  for (int i = 0; i < languageWidgetsList.size(); i++) {
    languageWidgetsList[i]->updateLanguage();
  }
}

// private slots ==============================================================

void SettingsWindow::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "addButton")           addLanguageWidget(true, LANG::EMPTY, "", "");
  else if (objName == "deleteButton")   deleteLanguageWidgets();
  else if (objName == "dataPathButton") ui->dataPathEdit->setText(GetDirectoryPath(tr("Choose directory")));
  else if (objName == "cancelButton")   emit buttonClicked(MODE::CLOSE);
  else if (objName == "saveButton") {
    // save compressing level
    settings->setSetting("compressing/compressing_level", ui->compressingBox->getValue());
    // save data path
    QString tmp = ui->dataPathEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataDirectoryName;
    if (tmp.back() != '/') tmp.append('/');
    settings->setSetting("paths/data_directory", tmp);
    // save language widgets
    for (int i = 0; i < languageWidgetsList.size(); i++) {
      languageWidgetsList[i]->save();
    }
  }
}

// private methods ============================================================

void SettingsWindow::addLanguageWidget(bool deletable, LANG language, const QString &locFileName, const QString &textFileName) {
  LanguageWidget *lw = new LanguageWidget();
  languageWidgetsList.push_back(lw);
  lw->setDeletable(deletable);
  lw->setLanguage(language);
  lw->setLocFileName(locFileName);
  lw->setTextFileName(textFileName);
  Delay(0); // used for smooth render added widget; i have no idea how it work
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


