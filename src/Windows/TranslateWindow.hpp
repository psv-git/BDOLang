#ifndef TRANSLATEWINDOW_HPP
#define TRANSLATEWINDOW_HPP

#include <QWidget>
#include "ApplicationGlobal.hpp"

namespace Ui { class TranslateWindow; }
class WindowsHandler;


class TranslateWindow : public QWidget {
Q_OBJECT

public:
  explicit TranslateWindow(WindowsHandler *parent = 0);
  ~TranslateWindow();

signals:


public slots:
  void show(const QString &inFilePath, const QString &outFilePath);
  void hide();
  void onButtonClick();

private:
  WindowsHandler *parent;
  Ui::TranslateWindow *ui;

  bool isError;

};


#endif // TRANSLATEWINDOW_HPP
