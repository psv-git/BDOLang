#ifndef PROCESSINGWINDOW_HPP
#define PROCESSINGWINDOW_HPP

#include "ApplicationGlobal.hpp"

namespace Ui { class ProcessingWindow; }


class ProcessingWindow : public QWidget {
Q_OBJECT

public:
  explicit ProcessingWindow(QWidget *parent = nullptr);
  ~ProcessingWindow();

signals:
  void buttonClicked(MODE mode);

public slots:
  void show(MODE mode, const QString &srcFilePath, const QString &targFilePath);

private slots:
  void onButtonClick();

private:
  Ui::ProcessingWindow *ui = nullptr;
  bool isError = false;

};


#endif // PROCESSINGWINDOW_HPP
