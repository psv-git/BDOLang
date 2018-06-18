#ifndef WINDOWSHANDLER_HPP
#define WINDOWSHANDLER_HPP

#include <QApplication>
#include "ApplicationGlobal.hpp"

class QWidget;
class QString;
class MainWindow;
class TranslateWindow;
class ChooseFileWindow;
class ChooseFilesWindow;
class SettingsWindow;


class WindowsHandler {

public:
    WindowsHandler();
    ~WindowsHandler();

    void onButtonClick(QWidget *sender, MODE mode);
    void onButtonClick(QWidget *sender, const QString &inFile, const QString &outFile);

private:
    MODE mode;
    MainWindow *mainWindow = nullptr;
    TranslateWindow *translateWindow = nullptr;
    SettingsWindow *settingsWindow = nullptr;
    ChooseFileWindow *chooseFileWindow = nullptr;
    ChooseFilesWindow *chooseFilesWindow = nullptr;

};


#endif // WINDOWSHANDLER_HPP
