#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "CustomComboBox.hpp"
#include "LanguageWidget.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
  settingsHandler = &SettingsHandler::getInstance();
  languageHandler = &LanguageHandler::getInstance();
  languageHandler->setHandledObject(this);
  initUi();
}


SettingsWindow::~SettingsWindow() {
  delete ui;
  for (int i = 0; i < languageWidgetsList.size(); i++) {
    if (!languageWidgetsList.at(i)) delete languageWidgetsList[i];
  }
}

// events =====================================================================

void SettingsWindow::closeEvent(QCloseEvent *event) {
  emit buttonClicked(MODE::CLOSE);
  QWidget::closeEvent(event);
}

// public slots ===============================================================

void SettingsWindow::show() {
  ui->compressingBox->setValue(settingsHandler->getSetting("", "compressing_level", 1).toInt());
  ui->dataPathEdit->setText(settingsHandler->getSetting("", "data_path", DEFAULT_SETTINGS.dataDirectoryName).toString());
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
    settingsHandler->setSetting("", "compressing_level", ui->compressingBox->getValue());
    // save data path
    QString tmp = ui->dataPathEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataDirectoryName;
    settingsHandler->setSetting("", "data_path", tmp);
    // save language widgets
    for (int i = 0; i < languageWidgetsList.size(); i++) {
      languageWidgetsList[i]->save();
    }
    settingsHandler->saveSettings();
    emit buttonClicked(MODE::CLOSE);
  }
}

// private methods ============================================================

void SettingsWindow::initUi() {
  ui->setupUi(this);

  ui->addButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));
  ui->deleteButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  ui->dataPathLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));
  ui->dataPathEdit->setFont(settingsHandler->getFont("Liberation Mono", "Regular", 10));
  ui->dataPathButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  ui->compressingLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));
  ui->compressingBox->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  ui->aboutEdit->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));

  ui->saveButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));
  ui->cancelButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(ui->saveButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->addButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->deleteButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->dataPathButton, SIGNAL(released()), this, SLOT(buttonClick()));

  addLanguageWidgets();
}


void SettingsWindow::addLanguageWidgets() {
  QStringList groups = settingsHandler->getGroups();
  for (int i = 0; i < groups.size(); i++) {
    LANG language = languageHandler->toLang(groups[i]);
    if (language != LANG::NONE) {
      QString locFileName = settingsHandler->getSetting(groups[i], "loc_file_name", "").toString();
      QString textFileName = settingsHandler->getSetting(groups[i], "text_file_name", "").toString();
      addLanguageWidget(true, language, locFileName, textFileName);
    }
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
