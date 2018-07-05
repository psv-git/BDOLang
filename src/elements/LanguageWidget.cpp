#include "LanguageWidget.hpp"
#include "ui_LanguageWidget.h"


LanguageWidget::LanguageWidget(QWidget *parent) : QWidget(parent), m_ui(new Ui::LanguageWidget) {
  m_settingsHandler = &SettingsHandler::getInstance();
  m_languageHandler = &LanguageHandler::getInstance();
  initUi();
}


LanguageWidget::~LanguageWidget() {
  if (needToDelete()) {
    m_languageHandler->unblockLanguage(m_currentLanguage);
    m_settingsHandler->removeSetting(m_languageHandler->toString(m_currentLanguage));
  }
  delete m_ui;
}

// public methods =============================================================

bool LanguageWidget::needToDelete() {
  return m_ui->deletableCheckBox->isChecked();
}


void LanguageWidget::setDeletable(bool value) {
  m_ui->deletableCheckBox->setEnabled(value);
  m_ui->languageComboBox->setEnabled(value);
}


void LanguageWidget::setLanguage(LANG language) {
  if (!m_languageHandler->isLanguageBlocked(language)) {
    m_currentLanguage = language;
    int index = m_ui->languageComboBox->findData(language);
    m_ui->languageComboBox->setCurrentIndex(index);
    m_languageHandler->blockLanguage(language);
  }
}


void LanguageWidget::setLocFileName(const QString &fileName) {
  m_ui->locFileNameEdit->setText(fileName);
}


void LanguageWidget::setTextFileName(const QString &fileName) {
  m_ui->textFileNameEdit->setText(fileName);
}


void LanguageWidget::save() {
  if (m_currentLanguage != LANG::EMPTY) {
    if (!m_ui->locFileNameEdit->text().isEmpty() && !m_ui->textFileNameEdit->text().isEmpty()) {
      m_settingsHandler->setSetting(m_languageHandler->toString(m_currentLanguage), "loc_file_name", m_ui->locFileNameEdit->text());
      m_settingsHandler->setSetting(m_languageHandler->toString(m_currentLanguage), "text_file_name", m_ui->textFileNameEdit->text());
    }
  }
}


void LanguageWidget::updateLanguage() {
  LANG language = m_languageHandler->getLastChangedLanguage();
  if (language != m_currentLanguage) {
    if (m_languageHandler->isWasBlocking()) {
      int index = m_ui->languageComboBox->findData(language);
      m_ui->languageComboBox->removeItem(index);
    } else {
      m_ui->languageComboBox->addItem(m_languageHandler->toString(language), language);
    }
  }
}

// private slots ==============================================================

void LanguageWidget::update() {
  m_languageHandler->unblockLanguage(m_currentLanguage);
  m_currentLanguage = qvariant_cast<LANG>(m_ui->languageComboBox->currentData());
  m_languageHandler->blockLanguage(m_currentLanguage);
}


void LanguageWidget::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "locFileNameButton") m_ui->locFileNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
  else m_ui->textFileNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
}

// private methods ============================================================

void LanguageWidget::initUi() {
  m_ui->setupUi(this);

  m_ui->languageLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));
  m_ui->languageComboBox->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  m_ui->locFileNameLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));
  m_ui->locFileNameEdit->setFont(m_settingsHandler->getFont("Liberation Mono", "Regular", 10));
  m_ui->locFileNameButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  m_ui->textFileNameLabel->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 11));
  m_ui->textFileNameEdit->setFont(m_settingsHandler->getFont("Liberation Mono", "Regular", 10));
  m_ui->textFileNameButton->setFont(m_settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(m_ui->languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
  connect(m_ui->locFileNameButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(m_ui->textFileNameButton, SIGNAL(released()), this, SLOT(buttonClick()));

  // add possible languages into combo box
  for (LANG language : m_languageHandler->getAllLanguages().keys()) {
    if (!m_languageHandler->isLanguageBlocked(language)) m_ui->languageComboBox->addItem(m_languageHandler->getAllLanguages().value(language), language);
  }
}
