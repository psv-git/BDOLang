#ifndef CUSTOMCOMBOBOX_HPP
#define CUSTOMCOMBOBOX_HPP

#include <QComboBox>


class CustomComboBox : public QComboBox {
Q_OBJECT

public:
  CustomComboBox(QWidget *parent = 0);
  ~CustomComboBox();

  int getValue();
  void setValue(int value);

};


#endif // CUSTOMCOMBOBOX_HPP
