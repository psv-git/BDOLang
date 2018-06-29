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
  void closeEvent(QCloseEvent *event);

signals:
  void buttonClicked(MODE mode);

public slots:
  void show(const QString &srcFilePath, const QString &targFilePath, MODE mode);

private slots:
  void error();
  void complete();
  void buttonClick();

private:
  Ui::ProcessingWindow *ui = nullptr;
  SettingsHandler *settingsHandler = nullptr;
  ErrorHandler *errorHandler = nullptr;

  QThread *thread = nullptr;

  void initUi();

};


#endif // PROCESSINGWINDOW_HPP
