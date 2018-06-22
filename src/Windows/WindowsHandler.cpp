#include "WindowsHandler.hpp"
#include "MainWindow.hpp"
#include "TranslateWindow.hpp"
#include "SettingsWindow.hpp"
#include "ChooseFileWindow.hpp"
#include "ChooseFilesWindow.hpp"
#include "ProcessingWindow.hpp"


WindowsHandler::WindowsHandler() {
  mainWindow        = new MainWindow(this);
  translateWindow   = new TranslateWindow(this);
  settingsWindow    = new SettingsWindow(this);
  chooseFileWindow  = new ChooseFileWindow(this);
  chooseFilesWindow = new ChooseFilesWindow(this);
  processingWindow  = new ProcessingWindow(this);

  QErrorMessage::qtHandler()->setModal(true);

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

// ============================================================================

void WindowsHandler::onButtonClick(const QWidget *sender, MODE mode) {
  WindowsHandler::mode = mode;
  if (sender == mainWindow) {
    if (mode == MODE::EXIT) QApplication::quit();
    if (mode == MODE::SETTINGS) {
      mainWindow->hide();
      settingsWindow->show();
    } else {
      chooseFilesWindow->show(); // single file chooser not using now
    }
  } else if (sender == translateWindow) {
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


void WindowsHandler::onButtonClick(const QWidget *sender, const QString &srcFilePath, const QString &targFilePath) {
  chooseFilesWindow->hide(); // single file chooser not using now

  if (mode == MODE::TRANSLATE) {
    mainWindow->hide();
    translateWindow->show(srcFilePath, targFilePath);
  }

  if (mode == MODE::BIN_TO_TEXT || mode == MODE::TEXT_TO_BIN) {
    mainWindow->hide();
    processingWindow->show(mode, srcFilePath, targFilePath);
  }
}
