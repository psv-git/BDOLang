#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "CustomComboBox.hpp"
#include "LanguageWidget.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
  ui->setupUi(this);
  settings = &Settings::getInstance();
  languageHandler = &LanguageHandler::getInstance();
  languageHandler->setHandledObject(this);

  ui->saveButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->cancelButton->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->compressingBox->setFont(settings->getFont("Liberation Sans", "Bold", 12));
  ui->compressingLabel->setFont(settings->getFont("Liberation Sans", "Bold", 11));
  ui->aboutEdit->setFont(settings->getFont("Liberation Sans", "Bold", 10));

  connect(ui->saveButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->addButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->deleteButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->dataPathButton, SIGNAL(released()), this, SLOT(buttonClick()));

  loadLanguageWidgets();
}


SettingsWindow::~SettingsWindow() {
  delete ui;
  for (int i = 0; i < languageWidgetsList.size(); i++) {
    if (!languageWidgetsList.at(i)) delete languageWidgetsList[i];
  }
}

// public slots ===============================================================

void SettingsWindow::show() {
  ui->compressingBox->setValue(settings->getSetting("", "compressing_level", DEFAULT_SETTINGS.compressingLevel).toInt());
  ui->dataPathEdit->setText(settings->getSetting("", "data_path", DEFAULT_SETTINGS.dataDirectoryName).toString());
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
  if (objName == "addButton") addLanguageWidget(true, LANG::EMPTY, "", "");
  else if (objName == "deleteButton") deleteLanguageWidgets();
  else if (objName == "dataPathButton") ui->dataPathEdit->setText(GetDirectoryPath(tr("Choose directory")));
  else if (objName == "cancelButton") emit buttonClicked(MODE::CLOSE);
  else if (objName == "saveButton") {
    // save compressing level
    settings->setSetting("", "compressing_level", ui->compressingBox->getValue());
    // save data path
    QString tmp = ui->dataPathEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataDirectoryName;
    settings->setSetting("", "data_path", tmp);
    // save language widgets
    for (int i = 0; i < languageWidgetsList.size(); i++) {
      languageWidgetsList[i]->save();
    }
    settings->saveSettings();
    emit buttonClicked(MODE::CLOSE);
  }
}

// private methods ============================================================

void SettingsWindow::loadLanguageWidgets() {
  QMap<QString, QPair<QString, QString>> languagesMap = settings->getLanguageWidgetsSettings();
  for (auto language : languagesMap.keys()) {
    addLanguageWidget(true, languageHandler->toLang(language), languagesMap.value(language).first, languagesMap.value(language).second);
  }
}


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
