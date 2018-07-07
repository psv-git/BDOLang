#ifndef LOGHANDLER_HPP
#define LOGHANDLER_HPP

#include "GlobalFunctions.hpp"


class LogHandler {

public:
  static LogHandler& getInstance() {
    static LogHandler m_instance;
    return m_instance;
  }

  LogHandler(LogHandler const&) = delete;
  LogHandler& operator = (LogHandler const&) = delete;

  void addLogMessage(const QString &errorMessage);
  void saveLog();

private:
  LogHandler();
  ~LogHandler();

  QStringList m_logMessagesList;
  QFile m_logFile;

};


#endif // LOGHANDLER_HPP
