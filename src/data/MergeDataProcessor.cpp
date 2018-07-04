#include "MergeDataProcessor.hpp"
#include "DataRow.hpp"


MergeDataProcessor::MergeDataProcessor(QVector<DataRow*>& from, QVector<DataRow*>& to) {
  m_from = &from;
  m_to = &to;

  m_stepCount = m_from->size() + m_to->size();
  m_percentValue = static_cast<qint64>(m_stepCount / 100);
  if (m_percentValue == 0) m_percentValue = 1;

  if (m_from->isEmpty() || m_to->isEmpty()) m_isComplete = true;
  else m_sheetValue = m_to->at(m_beg)->getSheet();
}


MergeDataProcessor::~MergeDataProcessor() {}

// public slots ===============================================================

void MergeDataProcessor::process() {
  if (m_operationNumber == 1) saveSheetsRanges();
  if (m_operationNumber == 2) replaceTranslation();
}

// public methods =============================================================

bool MergeDataProcessor::isComplete() const {
  return m_isComplete;
}


bool MergeDataProcessor::isError() const {
  return m_isError;
}


int MergeDataProcessor::getProgress() const {
  return m_currentProgress;
}

// private methods ============================================================

void MergeDataProcessor::saveSheetsRanges() {
  try {
    if (!m_isError && !m_isComplete) {
      if (m_sheetValue != m_to->at(m_end)->getSheet()) {
        m_sheetsPositionsList.insert(m_sheetValue, qMakePair(m_beg, m_end));
        m_beg = m_end;
      }
      m_sheetValue = m_to->at(m_beg)->getSheet();
      m_stepCounter++;
      m_currentProgress = static_cast<int>(m_stepCounter / m_percentValue);
      m_end++;
      if (m_end == m_to->size()) {
        m_sheetsPositionsList.insert(m_sheetValue, qMakePair(m_beg, m_end));
        m_operationNumber = 2; // switch to replace method
      }
    }
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"MergeDataProcessor::saveSheetsRanges\" something went wrong.");
  }
}


void MergeDataProcessor::replaceTranslation() {
  // get translated row and replace original row, if it was finded
  // if original row was not finded - translated row will skiped
  try {
    if (!m_isError && !m_isComplete) {
      m_sheetValue = m_from->at(m_index)->getSheet();
      QPair<int, int> indexes = m_sheetsPositionsList.value(m_sheetValue, qMakePair(0, m_to->size()));
      m_beg = indexes.first;
      m_end = indexes.second;
      do {
        int i = m_beg + ((m_end - m_beg) / 2);
        if (*m_from->at(m_index) == *m_to->at(i)) {
          m_to->at(i)->setString(m_from->at(m_index)->getString());
          break;
        }
        if (*m_from->at(m_index) < *m_to->at(i)) m_end = i;
        else m_beg = i;
      } while (m_beg != m_end);
      m_stepCounter++;
      m_currentProgress = static_cast<int>(m_stepCounter / m_percentValue);
      m_index++;
      if (m_index == m_from->size()) m_isComplete = true;
    }
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"MergeDataProcessor::replaceTranslation\" something went wrong.");
  }
}
