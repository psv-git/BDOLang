#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

#include <QApplication>

class QWidget;
class QString;
class MainWindow;
class ChooseFileWindow;


class WindowsHandler {

public:
  WindowsHandler();
  ~WindowsHandler();

  void onButtonClick(QWidget *sender, int code);
  void onButtonClick(QWidget *sender, const QString &inFile, const QString &outFile);

private:
  MainWindow *mainWindow;
  ChooseFileWindow *chooseFileWindow;

};

#endif // WINDOWSHANDLER_HPP
