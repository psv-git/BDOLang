#ifndef CHOOSEFILESWINDOW_HPP
#define CHOOSEFILESWINDOW_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class ChooseFilesWindow; }
class WindowsHandler;


class ChooseFilesWindow : public QWidget {
Q_OBJECT

public:
  explicit ChooseFilesWindow(WindowsHandler *parent = nullptr);
  ~ChooseFilesWindow();

signals:


public slots:
  void show();
  void onButtonClick();

private:
  WindowsHandler        *parent = nullptr;
  Ui::ChooseFilesWindow *ui     = nullptr;

};


#endif // CHOOSEFILESWINDOW_HPP
