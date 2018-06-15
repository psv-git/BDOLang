#ifndef CHOOSEFILEWINDOW_HPP
#define CHOOSEFILEWINDOW_HPP

#include <QDialog>


namespace Ui { class ChooseFileWindow; }


class ChooseFileWindow : public QDialog {
Q_OBJECT

public:
  explicit ChooseFileWindow(QWidget *parent = 0);
  ~ChooseFileWindow();

signals:


public slots:


private:
  Ui::ChooseFileWindow *ui;

};

#endif // CHOOSEFILEWINDOW_HPP
