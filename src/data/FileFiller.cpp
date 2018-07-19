// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "FileFiller.hpp"


FileFiller::FileFiller(QDataStream& from, QDataStream& to) {
  m_from = &from;
  m_to = &to;

  m_from->device()->reset();

  m_stepCount = m_from->device()->size() - m_to->device()->size();
  if (m_stepCount <= 0) m_isComplete = true;
  else {
    m_percentValue = static_cast<qint64>(m_stepCount / 100);
    if (m_percentValue == 0) m_percentValue = 1;
  }
}


FileFiller::~FileFiller() {}

// public slots ===============================================================

void FileFiller::process() {
  fill();
}

// public methods =============================================================

bool FileFiller::isComplete() const {
  return m_isComplete;
}


bool FileFiller::isError() const {
  return m_isError;
}


int FileFiller::getProgress() const {
  return m_currentProgress;
}

// private methods ============================================================

void FileFiller::fill() {
  try {
    if (!m_isError && !m_isComplete) {
      qint64 diff = m_stepCount - m_stepCounter;
      if (diff > 48) {
        qint64 null = 0;
        *m_to << null << null << null << null << null << null;
        m_stepCounter += 48;
      } else {
        qint8 null = 0;
        *m_to << null;
        m_stepCounter += 1;
      }

      m_currentProgress = static_cast<int>(m_stepCounter / m_percentValue);
      if (m_stepCounter == m_stepCount) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"FileFiller::fill\" " + QString(err.what()));
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"FileFiller::fill\" something went wrong.");
  }
}
