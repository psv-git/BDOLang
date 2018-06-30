#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include "headers.hpp"

namespace Ui { class ErrorWindow; }


class ErrorHandler : QWidget {
Q_OBJECT

public:
  static ErrorHandler& getInstance() {
    static ErrorHandler instance;
    return instance;
  }

  ErrorHandler(ErrorHandler const&) = delete;
  ErrorHandler& operator = (ErrorHandler const&) = delete;

  void addErrorMessage(const QString &errorMessage);

public slots:
  void showMessage();

private slots:
  void buttonClick();

private:
  ErrorHandler(QWidget *parent = nullptr);
  ~ErrorHandler();

  Ui::ErrorWindow *ui = nullptr;
  QStringList errorsMessagesList;

};


#endif // ERRORHANDLER_HPP
