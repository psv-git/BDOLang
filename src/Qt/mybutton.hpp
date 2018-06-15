#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>


class MyButton : public QPushButton {
Q_OBJECT

public:
  explicit MyButton(QWidget *parent = 0);
  explicit MyButton(const QString &text, QWidget *parent = 0);
  ~MyButton();

signals:


public slots:


private:

};

#endif // MYBUTTON_H
