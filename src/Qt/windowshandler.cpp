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
  if (sender == mainWindow && code == 1) {
      mainWindow->hide();
      chooseFileWindow->show();
  }
}
