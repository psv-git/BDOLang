#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

#include <QApplication>

class QWidget;
class QString;
class MainWindow;
class TranslateWindow;
class ChooseFileWindow;
class ChooseFilesWindow;
class SettingsWindow;


class WindowsHandler {

public:
  WindowsHandler();
  ~WindowsHandler();

  void onButtonClick(QWidget *sender, int code);
  void onButtonClick(QWidget *sender, const QString &inFile, const QString &outFile);

private:
  MainWindow *mainWindow = nullptr;
  TranslateWindow *translateWindow = nullptr;
  ChooseFileWindow *chooseFileWindow = nullptr;
  ChooseFilesWindow *chooseFilesWindow = nullptr;
  SettingsWindow *settingsWindow = nullptr;

};


#endif // WINDOWSHANDLER_HPP
