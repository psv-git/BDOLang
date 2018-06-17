#ifndef TRANSLATEWINDOW_HPP
#define TRANSLATEWINDOW_HPP

#include <QWidget>

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
  void show(const QString &fileName);


private:
  WindowsHandler *parent;
  Ui::TranslateWindow *ui;

  DataHandler *dataHandler;

};


#endif // TRANSLATEWINDOW_HPP
