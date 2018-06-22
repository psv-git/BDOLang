#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

#include "ApplicationGlobal.hpp"

class MainWindow;
class TranslateWindow;
class ChooseFileWindow;
class ChooseFilesWindow;
class SettingsWindow;
class ProcessingWindow;


class WindowsHandler : QObject {
Q_OBJECT

public:
  WindowsHandler(QObject *parent = nullptr);
  ~WindowsHandler();

public slots:
  void onButtonClick(MODE mode);
  void onButtonClick(const QString &srcFilePath, const QString &targFilePath);

private:
  MainWindow        *mainWindow        = nullptr;
  TranslateWindow   *translateWindow   = nullptr;
  SettingsWindow    *settingsWindow    = nullptr;
  ChooseFileWindow  *chooseFileWindow  = nullptr;
  ChooseFilesWindow *chooseFilesWindow = nullptr;
  ProcessingWindow  *processingWindow  = nullptr;
  MODE              mode               = MODE::NONE;

  void createWindow(WTYPE type);

};


#endif // WINDOWSHANDLER_HPP
