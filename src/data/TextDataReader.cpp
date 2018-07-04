#include "TextDataReader.hpp"


TextDataReader::TextDataReader(QTextStream& from, QVector<DataRow*>& to) {
  m_from = &from;
  m_to = &to;

  m_from->device()->seek(0);
  m_from->resetStatus();
  m_from->setAutoDetectUnicode(true);
  m_from->skipWhiteSpace();

  m_fullSize = m_from->device()->size();
}


TextDataReader::~TextDataReader() {}

// ============================================================================

bool TextDataReader::isComplete() const {
  return m_isComplete;
}


bool TextDataReader::isError() const {
  return m_isError;
}


int TextDataReader::getProgress() const {
  return m_currentProgress;
}


void TextDataReader::read() {
  try {
    if (!m_isError && !m_isComplete) {
      QMutexLocker locker(&m_lock);
      DataRow* dataRow = new DataRow();
      dataRow->readTextDataFrom(*m_from);
      m_to->push_back(dataRow);
      qint64 currentSize = m_from->device()->pos();
      m_currentProgress = static_cast<int>((100 * currentSize) / m_fullSize);
      if (m_from->atEnd()) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataReader::process\" " + QString(err.what()));
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
