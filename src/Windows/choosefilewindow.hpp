#ifndef CHOOSEFILEWINDOW_HPP
#define CHOOSEFILEWINDOW_HPP

#include <QFileDialog>
#include "ApplicationGlobal.hpp"

namespace Ui { class ChooseFileWindow; }
class WindowsHandler;


class ChooseFileWindow : public QWidget {
Q_OBJECT

public:
    explicit ChooseFileWindow(WindowsHandler *parent = 0);
    ~ChooseFileWindow();

signals:


public slots:
    void show();
    void onButtonClick();

private:
    Ui::ChooseFileWindow *ui;
    WindowsHandler *parent;

};


#endif // CHOOSEFILEWINDOW_HPP
