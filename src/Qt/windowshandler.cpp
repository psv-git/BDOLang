#include "windowshandler.hpp"
#include "mainwindow.hpp"
#include "translatewindow.hpp"
#include "choosefilewindow.hpp"
#include "choosefileswindow.hpp"
#include "settingswindow.hpp"


WindowsHandler::WindowsHandler() {
  mainWindow = new MainWindow(this);
  translateWindow = new TranslateWindow(this);
  chooseFileWindow = new ChooseFileWindow(this);
  chooseFilesWindow = new ChooseFilesWindow(this);

  mainWindow->show();
}


WindowsHandler::~WindowsHandler() {
  if (mainWindow) delete mainWindow;
  if (translateWindow) delete translateWindow;
  if (chooseFileWindow) delete chooseFileWindow;
  if (chooseFilesWindow) delete chooseFilesWindow;
}

// ===========================================================================

void WindowsHandler::onButtonClick(QWidget *sender, int code) {
  if (sender == mainWindow) {
    if (code == 0) QApplication::quit();
    if (code == 1) chooseFilesWindow->show();
    if (code == 2) { int i = 0; }
    if (code == 3) chooseFileWindow->show();
  }
  if (sender == translateWindow) {
    if (code == 1) {
      translateWindow->hide();
      mainWindow->show();
    }
    if (code == 2) {
      translateWindow->hide();
      mainWindow->show();
    }
  }
  if (sender == chooseFileWindow) {
    if (code == 0) chooseFileWindow->hide();
  }
  if (sender == chooseFilesWindow) {
    if (code == 0) chooseFilesWindow->hide();
  }
}


void WindowsHandler::onButtonClick(QWidget *sender, const QString &inFile, const QString &outFile) {
  if (sender == chooseFileWindow) {
    chooseFileWindow->hide();
    mainWindow->hide();
    translateWindow->show(inFile);
  }
  if (sender == chooseFilesWindow) {
    chooseFileWindow->hide();
  }
}
