#include "translatewindow.hpp"
#include "ui_translatewindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"
#include "../Data/DataHandler.hpp"


TranslateWindow::TranslateWindow(WindowsHandler *parent) : ui(new Ui::TranslateWindow) {
  TranslateWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->saveButton, &MyButton::released, this, &TranslateWindow::onButtonClick);
  connect(ui->cancelButton, &MyButton::released, this, &TranslateWindow::onButtonClick);
}


TranslateWindow::~TranslateWindow() {
  if (dataHandler) delete dataHandler;
  delete ui;
}


void TranslateWindow::show(const QString &fileName) {
  dataHandler = new DataHandler();
  QWidget::show();
}


void TranslateWindow::hide() {
  QWidget::hide();
  delete dataHandler;
  dataHandler = nullptr;
}

// ===========================================================================

void TranslateWindow::onButtonClick () {
  MyButton* button = qobject_cast<MyButton*>(sender());
  if (button != NULL ) {
    QString name = button->objectName();
    if (name == "saveButton") {
      parent->onButtonClick(this, 1);
    }
    if (name == "cancelButton") {
      parent->onButtonClick(this, 2);
    }
  }
}
