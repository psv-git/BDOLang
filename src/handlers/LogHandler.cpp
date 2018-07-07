#include "LogHandler.hpp"


LogHandler::LogHandler() {
  m_logFile.setFileName(DEFAULT_SETTINGS.logFileName);
}


LogHandler::~LogHandler() {}

// public methods =============================================================

void LogHandler::addLogMessage(const QString &errorMessage) {
  m_logMessagesList.push_back(errorMessage);
}


void LogHandler::saveLog() {
  OpenFile(m_logFile, QIODevice::Append);
  QTextStream stream(&m_logFile);
  stream.setCodec("UTF-8");
  stream.setGenerateByteOrderMark(true);
  for (int i = 0; i < m_logMessagesList.size(); i++) {
    stream << m_logMessagesList.at(i);
  }
  m_logMessagesList.clear();
  CloseFile(m_logFile);
}
