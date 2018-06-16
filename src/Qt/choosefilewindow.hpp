#ifndef CHOOSEFILEWINDOW_HPP
#define CHOOSEFILEWINDOW_HPP

#include <QDialog>
#include <QFileDialog>

namespace Ui { class ChooseFileWindow; }
class WindowsHandler;


class ChooseFileWindow : public QDialog {
Q_OBJECT

public:
  explicit ChooseFileWindow(WindowsHandler *parent = 0);
  ~ChooseFileWindow();

signals:


public slots:
  void show();
  void onButtonClick();

private:
  WindowsHandler *parent;
  Ui::ChooseFileWindow *ui;

  const QString getFileName(const char* s);

};

#endif // CHOOSEFILEWINDOW_HPP
