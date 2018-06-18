#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include <QWidget>
#include "ApplicationGlobal.hpp"

namespace Ui { class SettingsWindow; }
class WindowsHandler;
class QString;


class SettingsWindow : public QWidget {
Q_OBJECT

public:
  explicit SettingsWindow(WindowsHandler *parent = 0);
  ~SettingsWindow();

signals:


public slots:
  void show();
  void onButtonClick();


private:
  WindowsHandler *parent;
  Ui::SettingsWindow *ui;

};


#endif // SETTINGSWINDOW_HPP
