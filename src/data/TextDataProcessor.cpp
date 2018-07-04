#include "TextDataProcessor.hpp"


TextDataProcessor::TextDataProcessor(QTextStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode) {
  m_stream = &stream;
  m_data = &data;
  m_mode = mode;

  m_stream->device()->seek(0);
  m_stream->resetStatus();
  if (mode == PROCESS_MODE::READ) {
    m_stream->setAutoDetectUnicode(true);
    m_stream->skipWhiteSpace();
    m_percentValue = static_cast<qint64>(m_stream->device()->size() / 100);
  }
  if (mode == PROCESS_MODE::WRITE) {
    m_stream->setCodec("UTF-8");
    m_stream->setGenerateByteOrderMark(true);
    m_maxCount = static_cast<qint64>(m_data->size());
    m_percentValue = static_cast<qint64>(m_maxCount / 100);
  }
}


TextDataProcessor::~TextDataProcessor() {}

// public slots  ==============================================================

void TextDataProcessor::process() {
  if (m_mode == PROCESS_MODE::READ) read();
  if (m_mode == PROCESS_MODE::WRITE) write();
}

// public methods  ============================================================

bool TextDataProcessor::isComplete() const {
  return m_isComplete;
}


bool TextDataProcessor::isError() const {
  return m_isError;
}


int TextDataProcessor::getProgress() const {
  return m_currentProgress;
}

// private methods ============================================================

void TextDataProcessor::read() {
  try {
    if (!m_isError && !m_isComplete) {
      DataRow* dataRow = new DataRow();
      dataRow->readTextDataFrom(*m_stream);
      m_data->push_back(dataRow);
      qint64 currentSize = m_stream->device()->pos();
      m_currentProgress = static_cast<int>(currentSize / m_percentValue);
      if (m_stream->atEnd()) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataProcessor::read\" " + QString(err.what()));
  }
  catch (std::bad_alloc) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataProcessor::read\" allocating memory was failed.");
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataProcessor::read\" something went wrong.");
  }
}


void TextDataProcessor::write() {
  try {
    if (!m_isError && !m_isComplete) {
      m_data->at(m_counter)->writeTextDataTo(*m_stream);
      m_counter++;
      m_currentProgress = static_cast<int>(m_counter / m_percentValue);
      if (m_counter == m_maxCount) m_isComplete = true;
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataProcessor::write\" " + QString(err.what()));
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"TextDataProcessor::write\" something went wrong.");
  }
}
