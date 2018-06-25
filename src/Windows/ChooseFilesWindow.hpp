#ifndef CHOOSEFILESWINDOW_HPP
#define CHOOSEFILESWINDOW_HPP

#include "ApplicationFunctions.hpp"

namespace Ui { class ChooseFilesWindow; }


class ChooseFilesWindow : public QWidget {
Q_OBJECT

public:
  explicit ChooseFilesWindow(QWidget *parent = nullptr);
  ~ChooseFilesWindow();

signals:
  void buttonClicked(MODE);
  void buttonClicked(const QString &srcFilePath, const QString &targFilePath);

public slots:
  void show();

private slots:
  void buttonClick();

private:
  Ui::ChooseFilesWindow *ui = nullptr;
  Settings *settings = nullptr;

};


#endif // CHOOSEFILESWINDOW_HPP
