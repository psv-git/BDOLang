#ifndef CUSTOMCOMBOBOX_HPP
#define CUSTOMCOMBOBOX_HPP

#include "ApplicationGlobal.hpp"


class CustomComboBox : public QComboBox {
Q_OBJECT

public:
  CustomComboBox(QWidget *parent = 0);
  ~CustomComboBox();

  int getCurrentValue();
  void setCurrentValue(int value);

};


#endif // CUSTOMCOMBOBOX_HPP
