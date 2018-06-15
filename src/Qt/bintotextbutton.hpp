#ifndef BINTOTEXTBUTTON_HPP
#define BINTOTEXTBUTTON_HPP

#include <QPushButton>


namespace Ui { class BinToTextButton; }


class BinToTextButton : public QPushButton {
Q_OBJECT

public:
  explicit BinToTextButton(QMainWindow *parent = 0);
  ~BinToTextButton();

signals:


public slots:


private:
  Ui::BinToTextButton *ui;

};

#endif // BINTOTEXTBUTTON_HPP
