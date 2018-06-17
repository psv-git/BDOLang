#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include <QWidget>

namespace Ui { class SettingsWindow; }
class WindowsHandler;


class SettingsWindow : public QWidget {
Q_OBJECT

public:
  explicit SettingsWindow(WindowsHandler *parent = 0);
  ~SettingsWindow();

signals:


public slots:


private:
  WindowsHandler *parent;
  Ui::SettingsWindow *ui;

};


#endif // SETTINGSWINDOW_HPP
