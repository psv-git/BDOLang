#ifndef CHOOSEFILEWINDOW_HPP
#define CHOOSEFILEWINDOW_HPP

#include <QFileDialog>

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

  const QString getFileName(const char* s);

};


#endif // CHOOSEFILEWINDOW_HPP
