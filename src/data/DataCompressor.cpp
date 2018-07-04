#include "DataCompressor.hpp"


DataCompressor::DataCompressor(QDataStream& from, QDataStream& to, PROCESS_MODE mode) {
  m_from = &from;
  m_to = &to;
  m_mode = mode;

  m_from->device()->reset();
  m_from->resetStatus();
  m_to->device()->reset();
  m_to->resetStatus();
}


DataCompressor::~DataCompressor() {
  if (m_inBuff) delete[] m_inBuff;
  if (m_outBuff) delete[] m_outBuff;
}

// ============================================================================

void DataCompressor::init() {
  try {
    m_inBuff = new uint8_t[m_buffSize];
    m_outBuff = new uint8_t[m_buffSize];

    if (m_mode == PROCESS_MODE::DECRYPT) {
      ReadDataFromStream(*m_from, m_expectedUncompressedDataSize, 4);
      m_fullSize = static_cast<qint64>(m_expectedUncompressedDataSize);
      if (inflateInit(&m_stream) != Z_OK) throw std::runtime_error("inflate init was failed.");
    }
    if (m_mode == PROCESS_MODE::ENCRYPT) {
      m_uncompressedDataSize = static_cast<unsigned long>(m_from->device()->size());
      WriteDataToStream(*m_to, m_uncompressedDataSize, 4);
      int level = SettingsHandler::getInstance().getSetting("", "compressing_level", 1).toInt();
      if (deflateInit(&m_stream, level) != Z_OK) throw std::runtime_error("deflate init was failed.");
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"DataCompressor::init\" " + QString(err.what()));
  }
  catch (std::bad_alloc) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"DataCompressor::init\" allocating memory was failed.");
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"DataCompressor::init\" something went wrong.");
  }
}


bool DataCompressor::isComplete() const {
  return m_isComplete;
}


bool DataCompressor::isError() const {
  return m_isError;
}


int DataCompressor::getProgress() const {
  return m_currentProgress;
}


void DataCompressor::process() {
  if (m_mode == PROCESS_MODE::DECRYPT) uncompressing();
  if (m_mode == PROCESS_MODE::ENCRYPT) compressing();
}


void DataCompressor::compressing() {
  try {
    if (!m_isError && !m_isComplete) {
      m_stream.avail_in = static_cast<unsigned int>(ReadDataFromStream(*m_from, *m_inBuff, static_cast<int>(m_buffSize)));
      m_stream.next_in = m_inBuff;
      int flush = (m_from->device()->atEnd()) ? Z_FINISH : Z_NO_FLUSH;
      int result = Z_OK;
      do {
        m_stream.avail_out = m_buffSize;
        m_stream.next_out = m_outBuff;
        int result = deflate(&m_stream, flush);
        if (result == Z_STREAM_ERROR || result == Z_BUF_ERROR) throw std::runtime_error("deflate was failed.");
        int have = static_cast<int>(m_buffSize - m_stream.avail_out);
        if (have > 0) WriteDataToStream(*m_to, *m_outBuff, have);
      } while (m_stream.avail_out == 0);
      unsigned long currentSize = static_cast<unsigned long>(m_from->device()->pos());
      m_currentProgress = static_cast<int>((100 * currentSize) / m_uncompressedDataSize);
      if (flush == Z_FINISH) {
        m_isComplete = true;
        deflateEnd(&m_stream);
        if (result != Z_STREAM_END) throw std::runtime_error("compressed was failed.");
      }
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"DataCompressor::process\" " + QString(err.what()));
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"DataCompressor::process\" something went wrong.");
  }
}


void DataCompressor::uncompressing() {
  try {
    if (!m_isError && !m_isComplete) {
      int result = ReadDataFromStream(*m_from, *inBuff, m_buffSize);
      m_stream.avail_in = static_cast<unsigned int>(result); // negative value get throw in read function
      m_stream.next_in = m_inBuff;
      if (m_stream.avail_in == 0) m_isComplete = true;
      if (!m_isComplete) {
        do {
          m_stream.avail_out = m_buffSize;
          m_stream.next_out = m_outBuff;
          result = inflate(&m_stream, Z_NO_FLUSH);
          if (result != Z_OK && result != Z_STREAM_END) throw std::runtime_error("inflate was failed.");
          int have = m_buffSize - m_stream.avail_out; // decompressed data size
          m_uncompressedDataSize += have;
          if (have > 0) WriteDataToStream(*m_to, *m_outBuff, have); // write decompressed data to out file
        } while (m_stream.avail_out == 0);
        m_currentProgress = static_cast<int>((100 * m_uncompressedDataSize) / m_expectedUncompressedDataSize);
        if (result == Z_STREAM_END) {
          m_isComplete = true;
          if (m_uncompressedDataSize != m_expectedUncompressedDataSize) throw std::runtime_error("bad decompressed data length.");
        }
      }
    }
  }
  catch (const std::runtime_error &err) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"DataCompressor::process\" " + QString(err.what()));
  }
  catch (...) {
    m_isError = true;
    ErrorHandler::getInstance().addErrorMessage("In function \"DataCompressor::process\" something went wrong.");
  }
}
