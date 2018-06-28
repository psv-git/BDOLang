#include "WindowsHandler.hpp"
#include "MainWindow.hpp"
#include "ChooseFilesWindow.hpp"
#include "SettingsWindow.hpp"
#include "ProcessingWindow.hpp"
#include "TranslatingWindow.hpp"


WindowsHandler::WindowsHandler(QObject *parent) : QObject(parent) {
  createWindow(WTYPE::MAINW);
  createWindow(WTYPE::SETTW);
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
     if (!chooseFilesWindow) createWindow(WTYPE::CFSW);
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
    if (!processingWindow) createWindow(WTYPE::PROCW);
    processingWindow->show(srcFilePath, targFilePath, mode);
  }
}

// private methods ============================================================

// TODO: to template fabric
void WindowsHandler::createWindow(WTYPE type) {
  if (type == WTYPE::MAINW) {
    mainWindow = new MainWindow();
    connect(mainWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(buttonClick(MODE)));
  } else if (type == WTYPE::CFSW) {
    chooseFilesWindow =  new ChooseFilesWindow();
    connect(chooseFilesWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(buttonClick(MODE)));
    connect(chooseFilesWindow, SIGNAL(buttonClicked(const QString&, const QString&)), this, SLOT(buttonClick(const QString&, const QString&)));
    connect(chooseFilesWindow, SIGNAL(buttonClicked(MODE)), mainWindow, SLOT(unlockWindow()));
  } else if (type == WTYPE::SETTW) {
    settingsWindow = new SettingsWindow();
    connect(settingsWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(buttonClick(MODE)));
    connect(settingsWindow, SIGNAL(buttonClicked(MODE)), mainWindow, SLOT(unlockWindow()));
  } else if (type == WTYPE::PROCW) {
    processingWindow = new ProcessingWindow();
    connect(processingWindow, SIGNAL(buttonClicked(MODE)),  this, SLOT(buttonClick(MODE)));
    connect(processingWindow, SIGNAL(buttonClicked(MODE)), mainWindow, SLOT(unlockWindow()));
  }
}
