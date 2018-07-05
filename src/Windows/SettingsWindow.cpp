#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "CustomComboBox.hpp"
#include "LanguageWidget.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), m_ui(new Ui::SettingsWindow) {
  m_settingsHandler = &SettingsHandler::getInstance();
  m_languageHandler = &LanguageHandler::getInstance();
  m_languageHandler->setHandledObject(this);
  initUi();
}


SettingsWindow::~SettingsWindow() {
  delete m_ui;
  for (int i = 0; i < m_languageWidgetsList.size(); i++) {
    if (!m_languageWidgetsList.at(i)) delete m_languageWidgetsList[i];
  }
}

// events =====================================================================

void SettingsWindow::closeEvent(QCloseEvent *event) {
  emit buttonClicked(MODE::CLOSE);
  QWidget::closeEvent(event);
}

// public slots ===============================================================

void SettingsWindow::show() {
  m_ui->compressingBox->setValue(m_settingsHandler->getSetting("", "compressing_level", 1).toInt());
  m_ui->dataPathEdit->setText(m_settingsHandler->getSetting("", "data_path", DEFAULT_SETTINGS.dataDirectoryName).toString());
  QWidget::show();
}

// public methods =============================================================

void SettingsWindow::updateLanguage() {
  for (int i = 0; i < m_languageWidgetsList.size(); i++) {
    m_languageWidgetsList[i]->updateLanguage();
  }
}

// private slots ==============================================================

void SettingsWindow::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "addButton") addLanguageWidget(true, LANG::EMPTY, "", "");
  else if (objName == "deleteButton") deleteLanguageWidgets();
  else if (objName == "dataPathButton") m_ui->dataPathEdit->setText(GetDirectoryPath(tr("Choose directory")));
  else if (objName == "cancelButton") emit buttonClicked(MODE::CLOSE);
  else if (objName == "saveButton") {
    // save compressing level
    m_settingsHandler->setSetting("", "compressing_level", m_ui->compressingBox->getValue());
    // save data path
    QString tmp = m_ui->dataPathEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataDirectoryName;
    m_settingsHandler->setSetting("", "data_path", tmp);
    // save language widgets
    for (int i = 0; i < m_languageWidgetsList.size(); i++) {
      m_languageWidgetsList[i]->save();
    }
    m_settingsHandler->saveSettings();
    emit buttonClicked(MODE::CLOSE);
  }
}

// private methods ============================================================

void SettingsWindow::initUi() {
  m_ui->setupUi(this);

  m_ui->addButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->deleteButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  m_ui->dataPathLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));
  m_ui->dataPathEdit->setFont(m_settingsHandler->getFont("Liberation Mono", "Regular", 10));
  m_ui->dataPathButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  m_ui->compressingLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));
  m_ui->compressingBox->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  m_ui->aboutEdit->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));

  m_ui->saveButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));
  m_ui->cancelButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(m_ui->saveButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->addButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->deleteButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->dataPathButton, SIGNAL(released()), this, SLOT(buttonClick()));

  addLanguageWidgets();
}


void SettingsWindow::addLanguageWidgets() {
  QStringList groups = m_settingsHandler->getGroups();
  for (int i = 0; i < groups.size(); i++) {
    LANG language = m_languageHandler->toLang(groups[i]);
    if (language != LANG::NONE) {
      QString locFileName = m_settingsHandler->getSetting(groups[i], "loc_file_name", "").toString();
      QString textFileName = m_settingsHandler->getSetting(groups[i], "text_file_name", "").toString();
      addLanguageWidget(true, language, locFileName, textFileName);
    }
  }
}


void SettingsWindow::addLanguageWidget(bool deletable, LANG language, const QString &locFileName, const QString &textFileName) {
  LanguageWidget *lw = new LanguageWidget();
  m_languageWidgetsList.push_back(lw);
  lw->setDeletable(deletable);
  lw->setLanguage(language);
  lw->setLocFileName(locFileName);
  lw->setTextFileName(textFileName);
  Delay(0); // used for smooth render added widget; i have no idea how it work
  m_ui->scrollAreaContents->layout()->addWidget(lw);
}


void SettingsWindow::deleteLanguageWidgets() {
  for (auto it = m_languageWidgetsList.begin(); it != m_languageWidgetsList.end();) {
    if ((*it)->needToDelete()) {
      m_ui->scrollAreaContents->layout()->removeWidget(*it);
      delete *it;
      it = m_languageWidgetsList.erase(it);
    } else it++;
  }
}
