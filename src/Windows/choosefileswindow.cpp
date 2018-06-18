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
    QObject* obj = sender();
    QString objName = obj->objectName();
    if (objName == "okButton") {
        parent->onButtonClick(this, ui->pathEdit1->text(), ui->pathEdit2->text());
    }
    if (objName == "cancelButton") {
        parent->onButtonClick(this, MODE::CLOSE);
    }
    if (objName == "chooseButton1") {
        ui->pathEdit1->setText(getFileName("Files extensions (*)"));
    }
    if (objName == "chooseButton2") {
        ui->pathEdit2->setText(getFileName("Files extensions (*)"));
    }
}


const QString ChooseFilesWindow::getFileName(const char* s) {
    return QFileDialog::getOpenFileName(this, tr("Open file"), "./", tr(s));
}
