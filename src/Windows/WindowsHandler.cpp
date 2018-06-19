#include <QErrorMessage>
#include "WindowsHandler.hpp"
#include "MainWindow.hpp"
#include "TranslateWindow.hpp"
#include "SettingsWindow.hpp"
#include "ChooseFileWindow.hpp"
#include "ChooseFilesWindow.hpp"
#include "DataHandler.hpp"


WindowsHandler::WindowsHandler() {
  mode = MODE::NONE;
  mainWindow = new MainWindow(this);
  translateWindow = new TranslateWindow(this);
  settingsWindow = new SettingsWindow(this);
  chooseFileWindow = new ChooseFileWindow(this);
  chooseFilesWindow = new ChooseFilesWindow(this);

  QErrorMessage::qtHandler()->setModal(true);

  mainWindow->show();
}


WindowsHandler::~WindowsHandler() {
  if (mainWindow) delete mainWindow;
  if (translateWindow) delete translateWindow;
  if (settingsWindow) delete settingsWindow;
  if (chooseFileWindow) delete chooseFileWindow;
  if (chooseFilesWindow) delete chooseFilesWindow;
}

// ===========================================================================

void WindowsHandler::onButtonClick(QWidget *sender, MODE mode) {
  WindowsHandler::mode = mode;
  if (sender == mainWindow) {
    if (mode == MODE::MERGE) chooseFilesWindow->show();
    if (mode == MODE::BIN_TO_TEXT) chooseFileWindow->show();
    if (mode == MODE::TRANSLATE) chooseFilesWindow->show();
    if (mode == MODE::SETTINGS) {
      mainWindow->hide();
      settingsWindow->show();
    }
    if (mode == MODE::EXIT) QApplication::quit();
  }
  if (sender == translateWindow) {
    if (mode == MODE::CLOSE) {
      translateWindow->hide();
      mainWindow->show();
    }
  }
  if (sender == settingsWindow) {
    if (mode == MODE::CLOSE) {
      settingsWindow->hide();
      mainWindow->show();
    }
  }
  if (sender == chooseFileWindow) {
    if (mode == MODE::CLOSE) chooseFileWindow->hide();
  }
  if (sender == chooseFilesWindow) {
    if (mode == MODE::CLOSE) chooseFilesWindow->hide();
  }
}


void WindowsHandler::onButtonClick(QWidget *sender, const QString &srcFileName, const QString &targFileName) {
  QString srcName(srcFileName), targName(targFileName);
  if (srcName.isEmpty()) srcName = active_settings.sourceFileName;   // set defaults filenames
  if (targName.isEmpty()) targName = active_settings.targetFileName; // if files not chosen
  if (sender == chooseFilesWindow) {
    chooseFilesWindow->hide();
    if (mode == MODE::TRANSLATE) {
      mainWindow->hide();
      translateWindow->show(srcName, targName);
    }
  }
  if (sender == chooseFileWindow) {
    chooseFileWindow->hide();
    if (mode == MODE::BIN_TO_TEXT) {
      // TODO: сделатьь отдельное окно с прогрессом и перенести в него
      DataHandler::getInstance().convertBinFileToTextFile(srcName);
    }
  }
}
