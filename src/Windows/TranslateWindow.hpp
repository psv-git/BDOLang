#ifndef TRANSLATEWINDOW_HPP
#define TRANSLATEWINDOW_HPP

#include <QWidget>
#include "ApplicationGlobal.hpp"

namespace Ui { class TranslateWindow; }
class WindowsHandler;
class DataHandler;


class TranslateWindow : public QWidget {
Q_OBJECT

public:
  explicit TranslateWindow(WindowsHandler *parent = 0);
  ~TranslateWindow();

signals:


public slots:
  void load(const QString &fileName);
  void unload();
  void onButtonClick();


private:
  WindowsHandler *parent;
  Ui::TranslateWindow *ui;

  DataHandler *dataHandler;

};


#endif // TRANSLATEWINDOW_HPP
