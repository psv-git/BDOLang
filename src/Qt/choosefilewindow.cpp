#include "choosefilewindow.hpp"
#include "ui_choosefilewindow.h"


ChooseFileWindow::ChooseFileWindow(QWidget *parent) : QDialog(parent), ui(new Ui::ChooseFileWindow) {
  ui->setupUi(this);
}


ChooseFileWindow::~ChooseFileWindow() {
  delete ui;
}


//void ChooseFileWindow::onClickButton () {}
