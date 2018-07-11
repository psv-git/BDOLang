// Copyright (c) 2018 PSV
// https://github.com/psv-git

#include "CustomComboBox.hpp"


CustomComboBox::CustomComboBox(QWidget *parent) : QComboBox(parent) {}


CustomComboBox::~CustomComboBox() {}

// public methods =============================================================

int CustomComboBox::getValue() {
  return QComboBox::currentIndex() + 1;
}


void CustomComboBox::setValue(int value) {
  QComboBox::setCurrentIndex(value - 1);
}
