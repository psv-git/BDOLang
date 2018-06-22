#ifndef TRANSLATEWINDOW_HPP
#define TRANSLATEWINDOW_HPP

#include "ApplicationGlobal.hpp"

namespace Ui { class TranslateWindow; }
class WindowsHandler;


class TranslateWindow : public QWidget {
Q_OBJECT

public:
  explicit TranslateWindow(WindowsHandler *parent = nullptr);
  ~TranslateWindow();

signals:


public slots:
  void show(const QString &inFilePath, const QString &outFilePath);
  void hide();
  void onButtonClick();

private:
  WindowsHandler      *parent = nullptr;
  Ui::TranslateWindow *ui     = nullptr;
  bool                isError = false;

};


#endif // TRANSLATEWINDOW_HPP
