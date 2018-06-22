#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class SettingsWindow; }
class WindowsHandler;


class SettingsWindow : public QWidget {
Q_OBJECT

public:
  explicit SettingsWindow(WindowsHandler *parent = nullptr);
  ~SettingsWindow();

signals:


public slots:
  void show();
  void onButtonClick();

private:
  WindowsHandler     *parent = nullptr;
  Ui::SettingsWindow *ui     = nullptr;

};


#endif // SETTINGSWINDOW_HPP
