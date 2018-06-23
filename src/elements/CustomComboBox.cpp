#include "CustomComboBox.hpp"


CustomComboBox::CustomComboBox(QWidget *parent) : QComboBox(parent) {}


CustomComboBox::~CustomComboBox() {}

// public methods =============================================================

int CustomComboBox::getCurrentValue() {
  return QComboBox::currentIndex() + 1;
}


void CustomComboBox::setCurrentValue(int value) {
  QComboBox::setCurrentIndex(value - 1);
}
