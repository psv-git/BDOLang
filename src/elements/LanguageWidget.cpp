#include "LanguageWidget.hpp"
#include "ui_LanguageWidget.h"


LanguageWidget::LanguageWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LanguageWidget) {
  ui->setupUi(this);
}


LanguageWidget::~LanguageWidget() {
  delete ui;
}

// public methods =============================================================

bool LanguageWidget::needToDelete() {
  return ui->checkBox->isChecked();
}


void LanguageWidget::setDeletable(bool value) {
  ui->checkBox->setCheckable(value);
  ui->languageEdit->setReadOnly(!value);
  ui->languageEdit->setClearButtonEnabled(value);
}


void LanguageWidget::setLanguage(const QString &language) {
  ui->languageEdit->setText(language);
}


void LanguageWidget::setLocFileName(const QString &fileName) {
  ui->locFileNameEdit->setText(fileName);
}


void LanguageWidget::setTextFileName(const QString &fileName) {
  ui->textFileNameEdit->setText(fileName);
}
