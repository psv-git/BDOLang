#include "TextDataWriter.hpp"


TextDataWriter::TextDataWriter(QVector<DataRow*>& from, QTextStream& to) {
  m_from = &from;
  m_to = &to;

  m_to->device()->seek(0);
  m_to->resetStatus();
  m_to->setCodec("UTF-8");
  m_to->setGenerateByteOrderMark(true);

  m_maxCount = static_cast<qint64>(m_from->size());
}


TextDataWriter::~TextDataWriter() {}

// ============================================================================

bool TextDataWriter::isComplete() const {
  return m_isComplete;
}


bool TextDataWriter::isError() const {
  return m_isError;
}


int TextDataWriter::getProgress() const {
  return m_currentProgress;
}


void TextDataWriter::write() {
  try {
    if (!m_isError && !m_isComplete) {
      m_from->at(m_counter)->writeTextDataTo(*m_to);
      m_counter++;
      m_currentProgress = static_cast<int>((100 * m_counter) / m_maxCount);
      if (m_counter == m_maxCount) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataWriter::process\" " + QString(err.what()));
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataWriter::process\" something went wrong.");
  }
}
