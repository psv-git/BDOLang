#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

#include "ApplicationGlobal.hpp"

class MainWindow;
class TranslateWindow;
class ChooseFileWindow;
class ChooseFilesWindow;
class SettingsWindow;
class ProcessingWindow;


class WindowsHandler {

public:
  WindowsHandler();
  ~WindowsHandler();

  void onButtonClick(const QWidget *sender, MODE mode);
  void onButtonClick(const QWidget *sender, const QString &srcFilePath, const QString &targFilePath);

private:
  MainWindow        *mainWindow        = nullptr;
  TranslateWindow   *translateWindow   = nullptr;
  SettingsWindow    *settingsWindow    = nullptr;
  ChooseFileWindow  *chooseFileWindow  = nullptr;
  ChooseFilesWindow *chooseFilesWindow = nullptr;
  ProcessingWindow  *processingWindow  = nullptr;
  MODE              mode               = MODE::NONE;

};


#endif // WINDOWSHANDLER_HPP
