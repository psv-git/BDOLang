#ifndef CHOOSEFILESWINDOW_HPP
#define CHOOSEFILESWINDOW_HPP

#include <QFileDialog>
#include "ApplicationGlobal.hpp"

namespace Ui { class ChooseFilesWindow; }
class WindowsHandler;


class ChooseFilesWindow : public QWidget {
Q_OBJECT

public:
    explicit ChooseFilesWindow(WindowsHandler *parent = 0);
    ~ChooseFilesWindow();

signals:


public slots:
    void show();
    void onButtonClick();

private:
    WindowsHandler *parent;
    Ui::ChooseFilesWindow *ui;

};


#endif // CHOOSEFILESWINDOW_HPP
