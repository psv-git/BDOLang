#include "settingswindow.hpp"
#include "ui_settingswindow.h"
#include "mybutton.hpp"
#include "windowshandler.hpp"


SettingsWindow::SettingsWindow(WindowsHandler *parent) : ui(new Ui::SettingsWindow) {
    SettingsWindow::parent = parent;
    ui->setupUi(this);

    connect(ui->saveButton, &MyButton::released, this, &SettingsWindow::onButtonClick);
    connect(ui->cancelButton, &MyButton::released, this, &SettingsWindow::onButtonClick);
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
}
