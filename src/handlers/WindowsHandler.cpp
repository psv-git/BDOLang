#include "WindowsHandler.hpp"
#include "MainWindow.hpp"
#include "ChooseFilesWindow.hpp"
#include "SettingsWindow.hpp"
#include "ProcessingWindow.hpp"
#include "TranslatingWindow.hpp"


WindowsHandler::WindowsHandler(QObject *parent) : QObject(parent) {
  mainWindow = createWindow<MainWindow>(this);
  settingsWindow = createWindow<SettingsWindow>(this);
  mainWindow->show();
}


WindowsHandler::~WindowsHandler() {
  if (mainWindow)        delete mainWindow;
  if (chooseFilesWindow) delete chooseFilesWindow;
  if (settingsWindow)    delete settingsWindow;
  if (processingWindow)  delete processingWindow;
  if (translatingWindow) delete translatingWindow;
}

// public slots ===============================================================

void WindowsHandler::buttonClick(MODE mode) {
  WindowsHandler::mode = mode; // save mode from main window
  QObject *sender = QObject::sender();
  if (sender == mainWindow) {
    if (mode == MODE::EXIT) QApplication::quit();
    if (mode == MODE::SETTINGS) settingsWindow->show();
    else {
     if (!chooseFilesWindow) chooseFilesWindow = createWindow<ChooseFilesWindow>(this);
     chooseFilesWindow->show(mode);
    }
  } else if (sender == chooseFilesWindow) {
    chooseFilesWindow->hide();
  } else if (sender == settingsWindow) {
    settingsWindow->hide();
  } else if (sender == processingWindow) {
    processingWindow->hide();
    mainWindow->show();
  }
}


void WindowsHandler::buttonClick(const QString &srcFilePath, const QString &targFilePath) {
  chooseFilesWindow->hide();
  mainWindow->hide();
  if (mode == MODE::BIN_TO_TEXT || mode == MODE::TEXT_TO_BIN || mode == MODE::MERGE_TEXT || mode == MODE::MERGE_BIN) {
    if (!processingWindow) processingWindow = createWindow<ProcessingWindow>(this);
    processingWindow->show(srcFilePath, targFilePath, mode);
  }
}

// friend functions ===========================================================

template <typename WT>
WT*  createWindow(WindowsHandler *wh) {
  WT *nw;
  if (typeid(WT) == typeid(MainWindow)) {
    nw = new WT();
    nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
  } else if (typeid(WT) == typeid(ChooseFilesWindow)) {
    nw = new WT();
    nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
    nw->connect(nw, SIGNAL(buttonClicked(const QString&, const QString&)), wh, SLOT(buttonClick(const QString&, const QString&)));
    nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh->mainWindow, SLOT(unlockWindow()));
  } else if (typeid(WT) == typeid(SettingsWindow)) {
    nw = new WT();
    nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
    nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh->mainWindow, SLOT(unlockWindow()));
  }
  else if (typeid(WT) == typeid(ProcessingWindow)) {
    nw = new WT();
    nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh, SLOT(buttonClick(MODE)));
    nw->connect(nw, SIGNAL(buttonClicked(MODE)), wh->mainWindow, SLOT(unlockWindow()));
  }
  return nw;
}
