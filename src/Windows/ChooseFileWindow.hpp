#ifndef CHOOSEFILEWINDOW_HPP
#define CHOOSEFILEWINDOW_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class ChooseFileWindow; }
class WindowsHandler;


class ChooseFileWindow : public QWidget {
Q_OBJECT

public:
  explicit ChooseFileWindow(WindowsHandler *parent = nullptr);
  ~ChooseFileWindow();

signals:


public slots:
  void show();
  void onButtonClick();

private:
  Ui::ChooseFileWindow *ui     = nullptr;
  WindowsHandler       *parent = nullptr;

};


#endif // CHOOSEFILEWINDOW_HPP
