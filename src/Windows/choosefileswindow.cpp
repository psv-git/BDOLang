#include "choosefileswindow.hpp"
#include "ui_choosefileswindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"


ChooseFilesWindow::ChooseFilesWindow(WindowsHandler *parent) : ui(new Ui::ChooseFilesWindow) {
  ChooseFilesWindow::parent = parent;
  ui->setupUi(this);

  connect(ui->okButton, &MyButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->cancelButton, &MyButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton1, &MyButton::released, this, &ChooseFilesWindow::onButtonClick);
  connect(ui->chooseButton2, &MyButton::released, this, &ChooseFilesWindow::onButtonClick);
}


ChooseFilesWindow::~ChooseFilesWindow() {
  delete ui;
}


void ChooseFilesWindow::show() {
  ui->pathEdit1->setText("");
  ui->pathEdit2->setText("");
  QWidget::show();
}

// ===========================================================================

void ChooseFilesWindow::onButtonClick () {
  MyButton* button = qobject_cast<MyButton*>(sender());
  if (button != NULL ) {
    QString name = button->objectName();
    if (name == "okButton") {
      parent->onButtonClick(this, ui->pathEdit1->text(), ui->pathEdit2->text());
    }
    if (name == "cancelButton") {
      parent->onButtonClick(this, 0);
    }
    if (name == "chooseButton1") {
      ui->pathEdit1->setText(getFileName("Files extensions (*)"));
    }
    if (name == "chooseButton2") {
      ui->pathEdit2->setText(getFileName("Files extensions (*)"));
    }
  }
}


const QString ChooseFilesWindow::getFileName(const char* s) {
  return QFileDialog::getOpenFileName(this, tr("Open file"), "./", tr(s));
}
