#include "WindowsHandler.hpp"
#include "MainWindow.hpp"
#include "ChooseFilesWindow.hpp"
#include "SettingsWindow.hpp"
#include "ProcessingWindow.hpp"


WindowsHandler::WindowsHandler(QObject *parent) : QObject(parent) {
  m_mainWindow = createWindow<MainWindow>(this);
  m_settingsWindow = createWindow<SettingsWindow>(this);
  m_chooseFilesWindow = createWindow<ChooseFilesWindow>(this);
  m_processingWindow = createWindow<ProcessingWindow>(this);
  m_mainWindow->show();
}


WindowsHandler::~WindowsHandler() {
  if (m_mainWindow) delete m_mainWindow;
  if (m_chooseFilesWindow) delete m_chooseFilesWindow;
  if (m_settingsWindow) delete m_settingsWindow;
  if (m_processingWindow) delete m_processingWindow;
}

// public slots ===============================================================

void WindowsHandler::buttonClick(MODE mode) {
  m_mode = mode; // save mode from main window
  QObject *sender = QObject::sender();
  if (sender == m_mainWindow) {
    if (mode == MODE::EXIT) QApplication::quit();
    if (mode == MODE::SETTINGS) m_settingsWindow->show();
    else m_chooseFilesWindow->show(mode);
  } else if (sender == m_chooseFilesWindow) {
    m_chooseFilesWindow->hide();
  } else if (sender == m_settingsWindow) {
    m_settingsWindow->hide();
  } else if (sender == m_processingWindow) {
    m_processingWindow->hide();
    m_mainWindow->show();
  }
}


void WindowsHandler::buttonClick(const QString &srcFilePath, const QString &targFilePath) {
  m_chooseFilesWindow->hide();
  m_mainWindow->hide();
  m_processingWindow->show(srcFilePath, targFilePath, m_mode);
}

// friend functions ===========================================================

template <typename WT>
WT*  createWindow(WindowsHandler *wh) {
  WT *nw = nullptr;
  try {
    if (typeid(WT) == typeid(MainWindow)) {
      nw = new WT();
      nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
    } else if (typeid(WT) == typeid(ChooseFilesWindow)) {
      nw = new WT();
      nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
      nw->connect(nw, SIGNAL(buttonClicked(const QString&, const QString&)), wh, SLOT(buttonClick(const QString&, const QString&)));
      nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh->m_mainWindow, SLOT(unlockWindow()));
    } else if (typeid(WT) == typeid(SettingsWindow)) {
      nw = new WT();
      nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
      nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh->m_mainWindow, SLOT(unlockWindow()));
    }
    else if (typeid(WT) == typeid(ProcessingWindow)) {
      nw = new WT();
      nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
      nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh->m_mainWindow, SLOT(unlockWindow()));
    }
  }
  catch (...) {
    QApplication::quit(); // close application if window creating was failed
  }
  return nw;
}
