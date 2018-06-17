#include "choosefilewindow.hpp"
#include "ui_choosefilewindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"


ChooseFileWindow::ChooseFileWindow(WindowsHandler *parent) : ui(new Ui::ChooseFileWindow) {
  ChooseFileWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->okButton, &MyButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->cancelButton, &MyButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->chooseButton, &MyButton::released, this, &ChooseFileWindow::onButtonClick);
}


ChooseFileWindow::~ChooseFileWindow() {
  delete ui;
}


void ChooseFileWindow::show() {
  ui->lineEdit->setText("");
  QWidget::show();
}

// ===========================================================================

void ChooseFileWindow::onButtonClick () {
  MyButton* button = qobject_cast<MyButton*>(sender());
  if (button != NULL ) {
    QString name = button->objectName();
    if (name == "okButton") {
      parent->onButtonClick(this, ui->lineEdit->text(), "");
    }
    if (name == "cancelButton") {
      parent->onButtonClick(this, 0);
    }
    if (name == "chooseButton") {
      ui->lineEdit->setText(getFileName("Files extensions (*)"));
    }
  }
}


const QString ChooseFileWindow::getFileName(const char* s) {
  return QFileDialog::getOpenFileName(this, tr("Open file"), "./", tr(s));
}
