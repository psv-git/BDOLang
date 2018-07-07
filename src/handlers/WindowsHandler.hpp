#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

#include "ApplicationGlobal.hpp"

class MainWindow;
class ChooseFilesWindow;
class SettingsWindow;
class ProcessingWindow;


class WindowsHandler : public QObject {
Q_OBJECT

public:
  WindowsHandler(QObject *parent = nullptr);
  ~WindowsHandler();

public slots:
  void buttonClick(MODE mode);
  void buttonClick(const QString &srcFilePath, const QString &targFilePath, LANG language);

private:
  MODE m_mode = MODE::NONE;
  MainWindow *m_mainWindow = nullptr;
  ChooseFilesWindow *m_chooseFilesWindow = nullptr;
  SettingsWindow *m_settingsWindow = nullptr;
  ProcessingWindow *m_processingWindow = nullptr;

  template <typename WT>
  friend WT* createWindow(WindowsHandler *wh);

};


#endif // WINDOWSHANDLER_HPP
