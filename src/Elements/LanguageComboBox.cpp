#include "LanguageComboBox.hpp"


LanguageComboBox::LanguageComboBox(QWidget *parent) : QComboBox(parent) {}


LanguageComboBox::~LanguageComboBox() {}

// public methods =============================================================

LANG LanguageComboBox::getCurrentLanguage() {
  qint32 index = (qint32)QComboBox::currentIndex();
  return (LANG)index;
}


void LanguageComboBox::setCurrentLanguage(LANG language) {
  int index = (int)language;
  QComboBox::setCurrentIndex(index);
}
