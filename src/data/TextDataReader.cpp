#include "TextDataReader.hpp"


TextDataReader::TextDataReader(QTextStream& from, QVector<DataRow*>& to) {
  m_from = &from;
  m_to = &to;
  m_fullSize = m_from->device()->size();

  m_from->device()->seek(0);
  m_from->resetStatus();
  m_from->setAutoDetectUnicode(true);
  m_from->skipWhiteSpace();
}


TextDataReader::~TextDataReader() {}

// ============================================================================

bool TextDataReader::isComplete() {
  return m_isComplete;
}


bool TextDataReader::isError() {
  return m_isError;
}


int TextDataReader::getProgress() {
  return m_currentProgress;
}


void TextDataReader::process() {
  try {
    if (!m_isError && !m_isComplete) {
      QMutexLocker locker(&m_lock);
      DataRow* dataRow = new DataRow();
      if (!dataRow->readTextDataFrom(*m_from)) throw false;
      m_to->push_back(dataRow);
      qint64 currentSize = m_from->device()->pos();
      m_currentProgress = static_cast<int>((100 * currentSize) / m_fullSize);
      if (m_from->atEnd()) m_isComplete = true;
    }
  }
  catch (std::bad_alloc) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataReader::process\" allocating memory was failed.");
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataReader::process\" something went wrong.");
  }
}
