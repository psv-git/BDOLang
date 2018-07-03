#include "TextDataWriter.hpp"


TextDataWriter::TextDataWriter(QVector<DataRow*>& from, QTextStream& to) {
  m_from = &from;
  m_to = &to;
  m_maxCount = static_cast<qint64>(m_from->size());

  m_to->device()->seek(0);
  m_to->resetStatus();
  m_to->setCodec("UTF-8");
  m_to->setGenerateByteOrderMark(true);
}


TextDataWriter::~TextDataWriter() {}

// ============================================================================

bool TextDataWriter::isComplete() {
  return m_isComplete;
}


bool TextDataWriter::isError() {
  return m_isError;
}


int TextDataWriter::getProgress() {
  return m_currentProgress;
}


void TextDataWriter::process() {
  try {
    if (!m_isError && !m_isComplete) {
      QMutexLocker locker(&m_lock);
      if (!m_from->at(m_counter)->writeTextDataTo(*m_to)) throw false;
      m_counter++;
      m_currentProgress = static_cast<int>((100 * m_counter) / m_maxCount);
      if (m_counter == m_maxCount) m_isComplete = true;
    }
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataWriter::process\" something went wrong.");
  }
}
