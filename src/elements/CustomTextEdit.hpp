#ifndef CUSTOMTEXTEDIT_HPP
#define CUSTOMTEXTEDIT_HPP

#include "headers.hpp"
#include <QTextEdit>


class CustomTextEdit : public QTextEdit {
Q_OBJECT

public:
  CustomTextEdit(QWidget *parent = nullptr);
  ~CustomTextEdit();

protected:
  void mousePressEvent(QMouseEvent *event);

};


#endif // CUSTOMTEXTEDIT_HPP
