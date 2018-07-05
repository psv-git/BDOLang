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
  void start(const QString &msg);
  void stop();
  void fail();
  void buttonClick();

private:
  Ui::ProcessingWindow *m_ui = nullptr;
  SettingsHandler *m_settingsHandler = nullptr;
  ErrorHandler *m_errorHandler = nullptr;

  void initUi();

  void blockWindow();
  void unblockWindow();

};


#endif // PROCESSINGWINDOW_HPP
