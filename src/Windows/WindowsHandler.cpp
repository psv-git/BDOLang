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
    if (mode == MODE::BIN_TO_TEXT || mode == MODE::TEXT_TO_BIN) chooseFileWindow->show();
    if (mode == MODE::MERGE || mode == MODE::TRANSLATE) chooseFilesWindow->show();
    if (mode == MODE::SETTINGS) {
      mainWindow->hide();
      settingsWindow->show();
    }
    if (mode == MODE::EXIT) QApplication::quit();
  }
  if (sender == translateWindow) {
    translateWindow->hide();
    mainWindow->show();
  }
  if (sender == settingsWindow) {
    settingsWindow->hide();
    mainWindow->show();
  }
  if (sender == chooseFileWindow) chooseFileWindow->hide();
  if (sender == chooseFilesWindow) chooseFilesWindow->hide();
}


void WindowsHandler::onButtonClick(QWidget *sender, const QString &srcFilePath, const QString &targFilePath) {
  if (sender == chooseFilesWindow) {
    chooseFilesWindow->hide();
    if (mode == MODE::TRANSLATE) {
      mainWindow->hide();
      translateWindow->show(srcFilePath, targFilePath);
    }
  }
  if (sender == chooseFileWindow) {
    chooseFileWindow->hide();
    // TODO: сделатьь отдельное окно с прогрессом и перенести в него
    if (mode == MODE::BIN_TO_TEXT) {
      try { DataHandler::getInstance().convertBinFileToTextFile(srcFilePath); }
      catch (const std::exception &e) { QErrorMessage::qtHandler()->showMessage(QString(e.what())); }
    }
    if (mode == MODE::TEXT_TO_BIN) {
      try { DataHandler::getInstance().convertTextFileToBinFile(srcFilePath); }
      catch (const std::exception &e) { QErrorMessage::qtHandler()->showMessage(QString(e.what())); }
    }
  }
}
