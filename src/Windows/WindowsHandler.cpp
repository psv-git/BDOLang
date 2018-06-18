#include <QErrorMessage>
#include "WindowsHandler.hpp"
#include "MainWindow.hpp"
#include "TranslateWindow.hpp"
#include "SettingsWindow.hpp"
#include "ChooseFileWindow.hpp"
#include "ChooseFilesWindow.hpp"


WindowsHandler::WindowsHandler() {
    mainWindow = new MainWindow(this);
    translateWindow = new TranslateWindow(this);
    settingsWindow = new SettingsWindow(this);
    chooseFileWindow = new ChooseFileWindow(this);
    chooseFilesWindow = new ChooseFilesWindow(this);

    QErrorMessage::qtHandler()->setModal(true);

    mainWindow->show();
}


WindowsHandler::~WindowsHandler() {
    if (mainWindow) delete mainWindow;
    if (translateWindow) delete translateWindow;
    if (chooseFileWindow) delete chooseFileWindow;
    if (chooseFilesWindow) delete chooseFilesWindow;
    if (settingsWindow) delete settingsWindow;
}

// ===========================================================================

void WindowsHandler::onButtonClick(QWidget *sender, MODE mode) {
    WindowsHandler::mode = mode;
    if (sender == mainWindow) {
        if (mode == MODE::EXIT) QApplication::quit();
        if (mode == MODE::SETTINGS) {
            mainWindow->hide();
            settingsWindow->show();
        }
        if (mode == MODE::MERGE) chooseFilesWindow->show();
        if (mode == MODE::BIN_TO_TEXT) chooseFileWindow->show();
        if (mode == MODE::TRANSLATE) chooseFileWindow->show();
    }
    if (sender == translateWindow) {
        if (mode == MODE::CLOSE) {
            translateWindow->unload();
            mainWindow->show();
        }
    }
    if (sender == settingsWindow) {
        if (mode == MODE::CLOSE) {
            settingsWindow->hide();
            mainWindow->show();
        }
    }
    if (sender == chooseFileWindow) {
        if (mode == MODE::CLOSE) chooseFileWindow->hide();
    }
    if (sender == chooseFilesWindow) {
        if (mode == MODE::CLOSE) chooseFilesWindow->hide();
    }
}


void WindowsHandler::onButtonClick(QWidget *sender, const QString &inFile, const QString &outFile) {
    if (sender == chooseFileWindow) {
        chooseFileWindow->hide();
        if (mode == MODE::TRANSLATE) {
            mainWindow->hide();
            translateWindow->load(inFile);
        }
    }
    if (sender == chooseFilesWindow) {
        chooseFilesWindow->hide();
    }
}
