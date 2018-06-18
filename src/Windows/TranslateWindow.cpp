#include <QErrorMessage>
#include "TranslateWindow.hpp"
#include "ui_TranslateWindow.h"
#include "MyButton.hpp"
#include "WindowsHandler.hpp"
#include "DataHandler.hpp"
#include "FileFunctions.hpp"


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


void TranslateWindow::load(const QString &fileName) {
    dataHandler = new DataHandler();
    std::string path = fileName.toStdString();
    std::ifstream input;
    try {
        openInputFile(input, path, "TranslateWindow::show()");
        dataHandler->readDataFromBinFile(input);
        closeFile(input, path, "TranslateWindow::show()");
    }
    catch (const std::exception &e) {
        if (input.is_open()) closeFile(input, path, "TranslateWindow::show()");
        std::cerr << e.what() << std::endl;
        QErrorMessage *errMsgr = QErrorMessage::qtHandler();
        errMsgr->showMessage(QString(e.what()));
    }
    QWidget::show();
}


void TranslateWindow::unload() {
    delete dataHandler;
    dataHandler = nullptr;
    QWidget::hide();
}

// ===========================================================================

void TranslateWindow::onButtonClick () {
    QObject *obj = sender();
    QString objName = obj->objectName();
    if (objName == "saveButton") parent->onButtonClick(this, MODE::CLOSE);
    if (objName == "cancelButton") parent->onButtonClick(this, MODE::CLOSE);
}
