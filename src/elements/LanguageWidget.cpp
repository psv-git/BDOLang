#include "LanguageWidget.hpp"
#include "ui_LanguageWidget.h"


LanguageWidget::LanguageWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LanguageWidget) {
  settingsHandler = &SettingsHandler::getInstance();
  languageHandler = &LanguageHandler::getInstance();
  initUi();
}


LanguageWidget::~LanguageWidget() {
  if (needToDelete()) {
    languageHandler->unblockLanguage(currentLanguage);
    settingsHandler->removeSetting(languageHandler->toString(currentLanguage));
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
      settingsHandler->setSetting(languageHandler->toString(currentLanguage), "loc_file_name", ui->locFileNameEdit->text());
      settingsHandler->setSetting(languageHandler->toString(currentLanguage), "text_file_name", ui->textFileNameEdit->text());
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

// private methods ============================================================

void LanguageWidget::initUi() {
  ui->setupUi(this);

  ui->languageLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));
  ui->languageComboBox->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  ui->locFileNameLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));
  ui->locFileNameEdit->setFont(settingsHandler->getFont("Liberation Mono", "Regular", 10));
  ui->locFileNameButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  ui->textFileNameLabel->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 11));
  ui->textFileNameEdit->setFont(settingsHandler->getFont("Liberation Mono", "Regular", 10));
  ui->textFileNameButton->setFont(settingsHandler->getFont("Liberation Sans", "Bold", 12));

  connect(ui->languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
  connect(ui->locFileNameButton, SIGNAL(released()), this, SLOT(buttonClick()));
  connect(ui->textFileNameButton, SIGNAL(released()), this, SLOT(buttonClick()));

  // add possible languages into combo box
  for (LANG language : languageHandler->getAllLanguages().keys()) {
    if (!languageHandler->isLanguageBlocked(language)) ui->languageComboBox->addItem(languageHandler->getAllLanguages().value(language), language);
  }
}
