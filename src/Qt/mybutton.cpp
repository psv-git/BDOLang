#include "mybutton.hpp"


MyButton::MyButton(QWidget *parent) : QPushButton(parent) {}


MyButton::MyButton(const QString &text, QWidget *parent) : QPushButton(parent) {
  setText(text);
}


MyButton::~MyButton() {}
