#ifndef CHOOSEFILEWINDOW_HPP
#define CHOOSEFILEWINDOW_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class ChooseFileWindow; }


class ChooseFileWindow : public QWidget {
Q_OBJECT

public:
  explicit ChooseFileWindow(QWidget *parent = nullptr);
  ~ChooseFileWindow();

signals:
  void buttonClicked(MODE);
  void buttonClicked(const QString &srcFilePath, const QString &targFilePath);

public slots:
  void show();

private slots:
  void onButtonClick();

private:
  Ui::ChooseFileWindow *ui = nullptr;

};


#endif // CHOOSEFILEWINDOW_HPP
