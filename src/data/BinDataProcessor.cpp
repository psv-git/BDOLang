// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "BinDataProcessor.hpp"
#include "DataRow.hpp"


BinDataProcessor::BinDataProcessor(QDataStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode) {
  m_stream = &stream;
  m_data = &data;
  m_mode = mode;

  m_stream->device()->reset();
  m_stream->resetStatus();
  if (mode == PROCESS_MODE::READ) {
    m_percentValue = m_stream->device()->size() / 100;
  }
  if (mode == PROCESS_MODE::WRITE) {
    m_stepCount = static_cast<qint64>(m_data->size());
    m_percentValue = static_cast<qint64>(m_stepCount / 100);
  }
  if (m_percentValue == 0) m_percentValue = 1;
}


BinDataProcessor::~BinDataProcessor() {}

// public slots ===============================================================

void BinDataProcessor::process() {
  if (m_mode == PROCESS_MODE::READ) read();
  if (m_mode == PROCESS_MODE::WRITE) write();
}

// public methods =============================================================

bool BinDataProcessor::isComplete() const {
  return m_isComplete;
}


bool BinDataProcessor::isError() const {
  return m_isError;
}


int BinDataProcessor::getProgress() const {
  return m_currentProgress;
}

// private methods ============================================================

void BinDataProcessor::read() {
  try {
    if (!m_isError && !m_isComplete) {
      DataRow* dataRow = new DataRow();
      dataRow->readBinDataFrom(*m_stream);
      m_data->push_back(dataRow);
      qint64 currentSize = m_stream->device()->pos();
      m_currentProgress = static_cast<int>(currentSize / m_percentValue);
      if (m_stream->atEnd()) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"BinDataProcessor::read\" " + QString(err.what()));
  }
  catch (std::bad_alloc) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"BinDataProcessor::read\" allocating memory was failed.");
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"BinDataProcessor::read\" something went wrong.");
  }
}


void BinDataProcessor::write() {
  try {
    if (!m_isError && !m_isComplete) {
      m_data->at(m_stepCounter)->writeBinDataTo(*m_stream);
      m_stepCounter++;
      m_currentProgress = static_cast<int>(m_stepCounter / m_percentValue);
      if (m_stepCounter == m_stepCount) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"BinDataProcessor::write\" " + QString(err.what()));
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"BinDataProcessor::write\" something went wrong.");
  }
}
