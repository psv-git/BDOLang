#include "choosefilewindow.hpp"
#include "ui_choosefilewindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"


ChooseFileWindow::ChooseFileWindow(WindowsHandler *parent) : ui(new Ui::ChooseFileWindow) {
  ChooseFileWindow::parent = parent;
  ui->setupUi(this);
}


ChooseFileWindow::~ChooseFileWindow() {
  delete ui;
}

// ===========================================================================

void ChooseFileWindow::onButtonClick () {}
