#ifndef CHOOSEFILEWINDOW_HPP
#define CHOOSEFILEWINDOW_HPP

#include <QDialog>

namespace Ui { class ChooseFileWindow; }
class WindowsHandler;


class ChooseFileWindow : public QDialog {
Q_OBJECT

public:
  explicit ChooseFileWindow(WindowsHandler *parent = 0);
  ~ChooseFileWindow();

signals:


public slots:
  void onButtonClick();

private:
  WindowsHandler *parent;
  Ui::ChooseFileWindow *ui;

};

#endif // CHOOSEFILEWINDOW_HPP
