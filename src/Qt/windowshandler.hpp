#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

class QWidget;
class MainWindow;
class ChooseFileWindow;


class WindowsHandler {

public:
  WindowsHandler();
  ~WindowsHandler();

  void onButtonClick(QWidget *sender, int code);

private:
  MainWindow *mainWindow;
  ChooseFileWindow *chooseFileWindow;

};

#endif // WINDOWSHANDLER_HPP
