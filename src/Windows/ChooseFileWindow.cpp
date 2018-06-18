#include "ChooseFileWindow.hpp"
#include "ui_ChooseFileWindow.h"
#include "MyButton.hpp"
#include "WindowsHandler.hpp"
#include "ApplicationFunctions.hpp"


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
        ui->pathEdit->setText(GetFilePath(tr("Open file"), tr("Files extensions (*)")));
    }
}
