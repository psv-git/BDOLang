#ifndef TRANSLATEWINDOW_HPP
#define TRANSLATEWINDOW_HPP

#include "ApplicationGlobal.hpp"

namespace Ui { class TranslateWindow; }


class TranslateWindow : public QWidget {
Q_OBJECT

public:
  explicit TranslateWindow(QWidget *parent = nullptr);
  ~TranslateWindow();

signals:
  void buttonClicked(MODE mode);

public slots:
  void show(const QString &inFilePath, const QString &outFilePath);
  void hide();

private slots:
  void buttonClick();

private:
  Ui::TranslateWindow *ui = nullptr;

};


#endif // TRANSLATEWINDOW_HPP
