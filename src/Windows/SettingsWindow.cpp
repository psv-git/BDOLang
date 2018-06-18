#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "MyButton.hpp"
#include "WindowsHandler.hpp"
#include "ApplicationFunctions.hpp"


SettingsWindow::SettingsWindow(WindowsHandler *parent) : ui(new Ui::SettingsWindow) {
    SettingsWindow::parent = parent;
    ui->setupUi(this);

    connect(ui->saveButton, &MyButton::released, this, &SettingsWindow::onButtonClick);
    connect(ui->cancelButton, &MyButton::released, this, &SettingsWindow::onButtonClick);
    connect(ui->chooseButton1, &MyButton::released, this, &SettingsWindow::onButtonClick);
    connect(ui->chooseButton2, &MyButton::released, this, &SettingsWindow::onButtonClick);
    connect(ui->chooseButton3, &MyButton::released, this, &SettingsWindow::onButtonClick);
}


SettingsWindow::~SettingsWindow() {
    delete ui;
}

// ===========================================================================

void SettingsWindow::onButtonClick() {
    QObject *obj = sender();
    QString objName = obj->objectName();
    if (objName == "cancelButton") parent->onButtonClick(this, MODE::CLOSE);
    if (objName == "saveButton") parent->onButtonClick(this, MODE::CLOSE);
    if (objName == "chooseButton1") ui->filePathEdit->setText(GetDirectory(tr("Choose directory")));
    if (objName == "chooseButton2") ui->fileNameEdit1->setText(GetFileName(tr("Choose file"),  tr("Files extensions (*)")));
    if (objName == "chooseButton3") ui->fileNameEdit2->setText(GetFileName(tr("Choose file"),  tr("Files extensions (*)")));
}
