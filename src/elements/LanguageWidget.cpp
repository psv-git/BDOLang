#include "LanguageWidget.hpp"
#include "ui_LanguageWidget.h"


LanguageWidget::LanguageWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LanguageWidget) {
  ui->setupUi(this);
  settings = &Settings::getInstance();
  languageHandler = &LanguageHandler::getInstance();

  // add possible languages into combo box
  for (LANG language : languageHandler->getAllLanguages().keys()) {
    if (!languageHandler->isLanguageBlocked(language)) ui->languageComboBox->addItem(languageHandler->getAllLanguages().value(language), language);
  }

  connect(ui->languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
  connect(ui->locFileNameButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->textFileNameButton, SIGNAL(released()), this, SLOT(buttonClick()));
}


LanguageWidget::~LanguageWidget() {
  if (needToDelete()) {
    languageHandler->unblockLanguage(currentLanguage);
    settings->removeSetting(languageHandler->toString(currentLanguage));
  }
  delete ui;
}

// public methods =============================================================

bool LanguageWidget::needToDelete() {
  return ui->deletableCheckBox->isChecked();
}


void LanguageWidget::setDeletable(bool value) {
  ui->deletableCheckBox->setEnabled(value);
  ui->languageComboBox->setEnabled(value);
}


void LanguageWidget::setLanguage(LANG language) {
  if (!languageHandler->isLanguageBlocked(language)) {
    currentLanguage = language;
    int index = ui->languageComboBox->findData(language);
    ui->languageComboBox->setCurrentIndex(index);
    languageHandler->blockLanguage(language);
  }
}


void LanguageWidget::setLocFileName(const QString &fileName) {
  ui->locFileNameEdit->setText(fileName);
}


void LanguageWidget::setTextFileName(const QString &fileName) {
  ui->textFileNameEdit->setText(fileName);
}


void LanguageWidget::save() {
  if (currentLanguage != LANG::EMPTY) {
    if (!ui->locFileNameEdit->text().isEmpty() && !ui->textFileNameEdit->text().isEmpty()) {
      settings->setSetting(languageHandler->toString(currentLanguage), "loc_file_name", ui->locFileNameEdit->text());
      settings->setSetting(languageHandler->toString(currentLanguage), "text_file_name", ui->textFileNameEdit->text());
    }
  }
}


void LanguageWidget::updateLanguage() {
  LANG language = languageHandler->getLastChangedLanguage();
  if (language != currentLanguage) {
    if (languageHandler->isWasBlocking()) {
      int index = ui->languageComboBox->findData(language);
      ui->languageComboBox->removeItem(index);
    } else {
      ui->languageComboBox->addItem(languageHandler->toString(language), language);
    }
  }
}

// private slots ==============================================================

void LanguageWidget::update() {
  languageHandler->unblockLanguage(currentLanguage);
  currentLanguage = qvariant_cast<LANG>(ui->languageComboBox->currentData());
  languageHandler->blockLanguage(currentLanguage);
}


void LanguageWidget::buttonClick() {
  QObject *obj = QObject::sender();
  QString objName = obj->objectName();
  if (objName == "locFileNameButton") ui->locFileNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
  else ui->textFileNameEdit->setText(GetFileName(tr("Choose file"), tr("Files extensions (*)")));
}
