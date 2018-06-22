#ifndef PROCESSINGWINDOW_HPP
#define PROCESSINGWINDOW_HPP

#include "ApplicationGlobal.hpp"

namespace Ui { class ProcessingWindow; }
class WindowsHandler;


class ProcessingWindow : public QWidget {
Q_OBJECT

public:
  explicit ProcessingWindow(WindowsHandler *parent = nullptr);
  ~ProcessingWindow();

signals:


public slots:
  void show(MODE mode, const QString &srcFilePath, const QString &targFilePath);
  void onButtonClick();

private:
  WindowsHandler       *parent = nullptr;
  Ui::ProcessingWindow *ui     = nullptr;
  bool                 isError = false;

};


#endif // PROCESSINGWINDOW_HPP
