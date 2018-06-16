#include "windowshandler.hpp"
#include "mainwindow.hpp"
#include "choosefilewindow.hpp"


WindowsHandler::WindowsHandler() {
  mainWindow = new MainWindow(this);
  chooseFileWindow = new ChooseFileWindow(this);

  mainWindow->show();
}


WindowsHandler::~WindowsHandler() {
  if (mainWindow) delete mainWindow;
  if (chooseFileWindow) delete chooseFileWindow;
}

// ===========================================================================

void WindowsHandler::onButtonClick(QWidget *sender, int code) {
  if (sender == mainWindow) {
    if (code == 0) QApplication::quit();
    if (code == 1) {
      mainWindow->hide();
      chooseFileWindow->show();
    }
  }
  if (sender == chooseFileWindow) {
    if (code == 0) {
      chooseFileWindow->hide();
      mainWindow->show();
    }
  }
}


void WindowsHandler::onButtonClick(QWidget *sender, const QString &inFile, const QString &outFile) {
  if (sender == chooseFileWindow) {
    chooseFileWindow->hide();
    mainWindow->show();
  }
}
