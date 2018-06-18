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
    ui->pathEdit->setText("");
    QWidget::show();
}

// ===========================================================================

void ChooseFileWindow::onButtonClick () {
    QObject* obj = sender();
    QString objName = obj->objectName();
    if (objName == "okButton") {
        parent->onButtonClick(this, ui->pathEdit->text(), "");
    }
    if (objName == "cancelButton") {
        parent->onButtonClick(this, MODE::CLOSE);
    }
    if (objName == "chooseButton") {
        ui->pathEdit->setText(getFileName("Files extensions (*)"));
    }
}


const QString ChooseFileWindow::getFileName(const char* s) {
    return QFileDialog::getOpenFileName(this, tr("Open file"), "./", tr(s));
}
