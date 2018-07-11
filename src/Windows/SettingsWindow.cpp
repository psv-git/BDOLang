// Copyright (c) 2018 PSV
// https://github.com/psv-git

#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "CustomComboBox.hpp"
#include "CustomTextEdit.hpp"
#include "LanguageWidget.hpp"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), m_ui(new Ui::SettingsWindow) {
  LanguageHandler::getInstance().setHandledObject(this);
  initUi();
}


SettingsWindow::~SettingsWindow() {
  delete m_ui;
  for (int i = 0; i < m_languageWidgetsList.size(); i++) {
    if (!m_languageWidgetsList.at(i)) delete m_languageWidgetsList[i];
  }
}

// events =====================================================================

bool SettingsWindow::event(QEvent *event) {
  if (event->type() == QEvent::Close) {
    emit buttonClicked(MODE::CLOSE);
  }
  return QWidget::event(event);
}

// public slots ===============================================================

void SettingsWindow::show() {
  m_ui->compressingBox->setValue(SettingsHandler::getInstance().getSetting("", "compressing_level", 1).toInt());
  m_ui->dataPathEdit->setText(SettingsHandler::getInstance().getSetting("", "data_path", DEFAULT_SETTINGS.dataDirectoryName).toString());
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
    SettingsHandler::getInstance().setSetting("", "compressing_level", m_ui->compressingBox->getValue());
    // save data path
    QString tmp = m_ui->dataPathEdit->text();
    if (tmp.isEmpty()) tmp = DEFAULT_SETTINGS.dataDirectoryName;
    SettingsHandler::getInstance().setSetting("", "data_path", tmp);
    // save language widgets
    for (int i = 0; i < m_languageWidgetsList.size(); i++) {
      m_languageWidgetsList[i]->save();
    }
    SettingsHandler::getInstance().saveSettings();
    emit buttonClicked(MODE::CLOSE);
  }
}

// private methods ============================================================

void SettingsWindow::initUi() {
  m_ui->setupUi(this);

  m_ui->addButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->deleteButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));

  m_ui->dataPathLabel->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 11));
  m_ui->dataPathEdit->setFont(SettingsHandler::getInstance().getFont("Liberation Mono", "Regular", 10));
  m_ui->dataPathButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));

  m_ui->compressingLabel->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 11));
  m_ui->compressingBox->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));

  m_ui->aboutEdit->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 11));

  m_ui->saveButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));
  m_ui->cancelButton->setFont(SettingsHandler::getInstance().getFont("Liberation Sans", "Bold", 12));

  connect(m_ui->saveButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->cancelButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->addButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->deleteButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->dataPathButton, SIGNAL(released()), this, SLOT(buttonClick()));

  setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

  addLanguageWidgets();
}


void SettingsWindow::addLanguageWidgets() {
  QStringList groups = SettingsHandler::getInstance().getGroups();
  for (int i = 0; i < groups.size(); i++) {
    LANG language = LanguageHandler::getInstance().toLang(groups[i]);
    if (language != LANG::NONE) {
      QString locFileName = SettingsHandler::getInstance().getSetting(groups[i], "loc_file_name", "").toString();
      QString textFileName = SettingsHandler::getInstance().getSetting(groups[i], "text_file_name", "").toString();
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
