#include "translatewindow.hpp"
#include "ui_translatewindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"
#include "../Data/DataHandler.hpp"


TranslateWindow::TranslateWindow(WindowsHandler *parent) : ui(new Ui::TranslateWindow) {
  TranslateWindow::parent = parent;
  ui->setupUi(this);

  dataHandler = new DataHandler();
}


TranslateWindow::~TranslateWindow() {
  delete ui;
  delete dataHandler;
}


void TranslateWindow::show(const QString &fileName) {
  QWidget::show();
}

// ===========================================================================
