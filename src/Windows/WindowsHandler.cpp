#include "WindowsHandler.hpp"
#include "MainWindow.hpp"
#include "TranslateWindow.hpp"
#include "SettingsWindow.hpp"
#include "ChooseFileWindow.hpp"
#include "ChooseFilesWindow.hpp"
#include "ProcessingWindow.hpp"


WindowsHandler::WindowsHandler(QObject *parent) : QObject(parent) {
  QErrorMessage::qtHandler()->setModal(true);
  createWindow(WTYPE::MAINW);
  mainWindow->show();
}


WindowsHandler::~WindowsHandler() {
  if (mainWindow)        delete mainWindow;
  if (translateWindow)   delete translateWindow;
  if (settingsWindow)    delete settingsWindow;
  if (chooseFileWindow)  delete chooseFileWindow;
  if (chooseFilesWindow) delete chooseFilesWindow;
  if (processingWindow)  delete processingWindow;
}

// public slots ===============================================================

void WindowsHandler::onButtonClick(MODE mode) {
  WindowsHandler::mode = mode;
  QObject *sender = QObject::sender();
  if (sender == mainWindow) {
    if (mode == MODE::EXIT) QApplication::quit();
    if (mode == MODE::SETTINGS) {
      if (!settingsWindow) createWindow(WTYPE::SETTW);
      mainWindow->hide();
      settingsWindow->show();
    } else {
      if (!chooseFilesWindow) createWindow(WTYPE::CFSW);
      chooseFilesWindow->show(); // single file chooser not using now
    }
  } else if (sender == translateWindow) { // mean CLOSE mode by default
    translateWindow->hide();
    mainWindow->show();
  } else if (sender == settingsWindow) {
    settingsWindow->hide();
    mainWindow->show();
  } else if (sender == processingWindow) {
    processingWindow->hide();
    mainWindow->show();
  } else if (sender == chooseFileWindow) {
    chooseFileWindow->hide();
  } else if (sender == chooseFilesWindow) {
    chooseFilesWindow->hide();
  }
}


void WindowsHandler::onButtonClick(const QString &srcFilePath, const QString &targFilePath) {
  chooseFilesWindow->hide(); // single file chooser not using now
  mainWindow->hide();
  if (mode == MODE::TRANSLATE) {
    if (!translateWindow) createWindow(WTYPE::TRANSW);
    translateWindow->show(srcFilePath, targFilePath);
  } else if (mode == MODE::BIN_TO_TEXT || mode == MODE::TEXT_TO_BIN) {
    if (!processingWindow) createWindow(WTYPE::PROCW);
    processingWindow->show(mode, srcFilePath, targFilePath);
  }
}

// private methods ============================================================

void WindowsHandler::createWindow(WTYPE type) {
  if (type == WTYPE::MAINW) {
    mainWindow = new MainWindow();
    connect(mainWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(onButtonClick(MODE)));
  } else if (type == WTYPE::TRANSW) {
    translateWindow = new TranslateWindow();
    connect(translateWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(onButtonClick(MODE)));
  } else if (type == WTYPE::SETTW) {
    settingsWindow = new SettingsWindow();
    connect(settingsWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(onButtonClick(MODE)));
  } else if (type == WTYPE::CFEW) {
    chooseFileWindow =  new ChooseFileWindow();
    connect(chooseFileWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(onButtonClick(MODE)));
    connect(chooseFileWindow, SIGNAL(buttonClicked(const QString&, const QString&)), this, SLOT(onButtonClick(const QString&, const QString&)));
  } else if (type == WTYPE::CFSW) {
    chooseFilesWindow =  new ChooseFilesWindow();
    connect(chooseFilesWindow, SIGNAL(buttonClicked(MODE)), this, SLOT(onButtonClick(MODE)));
    connect(chooseFilesWindow, SIGNAL(buttonClicked(const QString&, const QString&)), this, SLOT(onButtonClick(const QString&, const QString&)));
  } else if (type == WTYPE::PROCW) {
    processingWindow = new ProcessingWindow();
    connect(processingWindow, SIGNAL(buttonClicked(MODE)),  this, SLOT(onButtonClick(MODE)));
  }
}
