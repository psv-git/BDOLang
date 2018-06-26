#ifndef TRANSLATINGWINDOW_HPP
#define TRANSLATINGWINDOW_HPP

#include "ApplicationGlobal.hpp"

namespace Ui { class TranslatingWindow; }


class TranslatingWindow : public QWidget {
Q_OBJECT

public:
  explicit TranslatingWindow(QWidget *parent = nullptr);
  ~TranslatingWindow();

signals:
  void buttonClicked(MODE mode);

public slots:
  void show(const QString &inFilePath, const QString &outFilePath);
  void hide();

private slots:
  void buttonClick();

private:
  Ui::TranslatingWindow *ui = nullptr;

};


#endif // TRANSLATINGWINDOW_HPP
