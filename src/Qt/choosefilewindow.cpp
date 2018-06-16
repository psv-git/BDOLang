#include "choosefilewindow.hpp"
#include "ui_choosefilewindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"


ChooseFileWindow::ChooseFileWindow(WindowsHandler *parent) : ui(new Ui::ChooseFileWindow) {
  ChooseFileWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->okButton, &MyButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->cancelButton, &MyButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->chooseButton1, &MyButton::released, this, &ChooseFileWindow::onButtonClick);
  connect(ui->chooseButton2, &MyButton::released, this, &ChooseFileWindow::onButtonClick);
}


ChooseFileWindow::~ChooseFileWindow() {
  delete ui;
}

void ChooseFileWindow::show() {
  ui->lineEdit1->setText("");
  ui->lineEdit2->setText("");
  QWidget::show();
}

// ===========================================================================

void ChooseFileWindow::onButtonClick () {
  MyButton* button = qobject_cast<MyButton*>(sender());
  if (button != NULL ) {
    QString name = button->objectName();
    if (name == "okButton") {
      parent->onButtonClick(this, ui->lineEdit1->text(), ui->lineEdit2->text());
    }
    if (name == "cancelButton") {
      parent->onButtonClick(this, 0);
    }
    if (name == "chooseButton1") {
      ui->lineEdit1->setText(getFileName("Files extensions (*)"));
    }
    if (name == "chooseButton2") {
      ui->lineEdit2->setText(getFileName("Files extensions (*)"));
    }
  }
}


const QString ChooseFileWindow::getFileName(const char* s) {
  return QFileDialog::getOpenFileName(this, tr("Open file"), "./", tr(s));
}
