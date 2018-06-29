#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

#include "ApplicationGlobal.hpp"

class MainWindow;
class ChooseFilesWindow;
class SettingsWindow;
class ProcessingWindow;
class TranslatingWindow;


class WindowsHandler : public QObject {
Q_OBJECT

public:
  WindowsHandler(QObject *parent = nullptr);
  ~WindowsHandler();

public slots:
  void buttonClick(MODE mode);
  void buttonClick(const QString &srcFilePath, const QString &targFilePath);

private:
  MODE mode                            = MODE::NONE;
  MainWindow *mainWindow               = nullptr;
  ChooseFilesWindow *chooseFilesWindow = nullptr;
  SettingsWindow *settingsWindow       = nullptr;
  ProcessingWindow *processingWindow   = nullptr;
  TranslatingWindow *translatingWindow = nullptr;

  template <typename WT>
  friend WT* createWindow(WindowsHandler *wh);

};


#endif // WINDOWSHANDLER_HPP
