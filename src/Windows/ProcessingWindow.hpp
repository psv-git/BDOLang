#ifndef PROCESSINGWINDOW_HPP
#define PROCESSINGWINDOW_HPP

#include "ApplicationGlobal.hpp"

namespace Ui { class ProcessingWindow; }


class ProcessingWindow : public QWidget {
Q_OBJECT

public:
  explicit ProcessingWindow(QWidget *parent = nullptr);
  ~ProcessingWindow();

protected:
  bool event(QEvent* event);

signals:
  void buttonClicked(MODE mode);

public slots:
  void show(const QString &srcFilePath, const QString &targFilePath, MODE mode);

private slots:
  void complete();
  void error();
  void buttonClick();

private:
  Ui::ProcessingWindow *ui = nullptr;
  SettingsHandler *settingsHandler = nullptr;
  ErrorHandler *errorHandler = nullptr;

  void initUi();

};


#endif // PROCESSINGWINDOW_HPP
