#include "BinDataWriter.hpp"
#include "DataRow.hpp"


BinDataWriter::BinDataWriter(QVector<DataRow*>& from, QDataStream& to) {
  m_from = &from;
  m_to = &to;
  m_maxCount = static_cast<qint64>(m_from->size());

  to.device()->reset();
  to.resetStatus();
}


BinDataWriter::~BinDataWriter() {}

// ============================================================================

bool BinDataWriter::isComplete() const {
  return m_isComplete;
}


bool BinDataWriter::isError() const {
  return m_isError;
}


int BinDataWriter::getProgress() const {
  return m_currentProgress;
}


void BinDataWriter::write() {
  try {
    if (!m_isError && !m_isComplete) {
      m_from->at(m_counter)->writeBinDataTo(*m_to);
      m_counter++;
      m_currentProgress = static_cast<int>((100 * m_counter) / m_maxCount);
      if (m_counter == m_maxCount) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"BinDataWriter::process\" " + QString(err.what()));
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"BinDataWriter::process\" something went wrong.");
  }
}
