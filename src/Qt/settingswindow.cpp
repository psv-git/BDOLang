#include "settingswindow.hpp"
#include "ui_settingswindow.h"
#include "windowshandler.hpp"


SettingsWindow::SettingsWindow(WindowsHandler *parent) : ui(new Ui::SettingsWindow) {
  SettingsWindow::parent = parent;
  ui->setupUi(this);


}


SettingsWindow::~SettingsWindow() {
  delete ui;
}

// ===========================================================================
