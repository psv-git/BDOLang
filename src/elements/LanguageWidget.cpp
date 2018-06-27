#include "LanguageWidget.hpp"
#include "ui_LanguageWidget.h"


LanguageWidget::LanguageWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LanguageWidget) {
  ui->setupUi(this);
  languageHandler = &LanguageHandler::getInstance();
  for(LANG language : languageHandler->getLanguagesMap().keys()) {
    if (!languageHandler->isBlocked(language)) ui->languageComboBox->addItem(languageHandler->getLanguagesMap().value(language), language);
  }
  connect(ui->languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
}


LanguageWidget::~LanguageWidget() {
  languageHandler->unblockLanguage(this, qvariant_cast<LANG>(ui->languageComboBox->currentData()));
  delete ui;
}

// public methods =============================================================

bool LanguageWidget::needToDelete() {
  return ui->deletableCheckBox->isChecked();
}


void LanguageWidget::setDeletable(bool value) {
  ui->deletableCheckBox->setCheckable(value);
  ui->languageComboBox->setEnabled(value);
}


void LanguageWidget::setLanguage(LANG language) {
  if (!languageHandler->isBlocked(language)) {
    currentLanguage = language;
    int index = ui->languageComboBox->findData(language);
    ui->languageComboBox->setCurrentIndex(index);
    if (language != LANG::EMPTY) languageHandler->blockLanguage(this, language);
  }
}


void LanguageWidget::setLocFileName(const QString &fileName) {
  ui->locFileNameEdit->setText(fileName);
}


void LanguageWidget::setTextFileName(const QString &fileName) {
  ui->textFileNameEdit->setText(fileName);
}

// public slots ===============================================================

void LanguageWidget::addLanguage(LANG language) {
  if (language != LANG::EMPTY) ui->languageComboBox->addItem(languageHandler->toString(language), language);
}


void LanguageWidget::removeLanguage(LANG language) {
  if (language != LANG::EMPTY) {
    int index = ui->languageComboBox->findData(language);
    ui->languageComboBox->removeItem(index);
  }
}

// private slots ==============================================================

void LanguageWidget::update() {
  LANG newLanguage =  qvariant_cast<LANG>(ui->languageComboBox->currentData());
  if (currentLanguage != LANG::EMPTY) languageHandler->unblockLanguage(this, currentLanguage);
  if (newLanguage != LANG::EMPTY) languageHandler->blockLanguage(this, newLanguage);
  currentLanguage = newLanguage;
}
