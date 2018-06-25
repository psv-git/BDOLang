#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include "ApplicationHeaders.hpp"


class ErrorHandler {

public:
  static ErrorHandler& getInstance() {
    static ErrorHandler instance;
    return instance;
  }

  ErrorHandler(ErrorHandler const&)              = delete;
  ErrorHandler& operator = (ErrorHandler const&) = delete;

  void addException(const QString &exceptionMessage);
  void showMessage();

private:
  ErrorHandler();
  ~ErrorHandler();

  QStringList exceptionsMessagesList;

};


#endif // ERRORHANDLER_HPP
