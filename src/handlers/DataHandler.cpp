#include "DataHandler.hpp"
#include "DataRow.hpp"
#include "TextDataProcessor.hpp"
#include "BinDataProcessor.hpp"
#include "DataCompressor.hpp"
#include "MergeDataProcessor.hpp"


const char* TMP_FILE_NAME = "./data/tmp.bss";

// ============================================================================

DataHandler::DataHandler(const QString &fromFilePath, const QString &toFilePath, LANG language, MODE mode) {
  m_settingsHandler = &SettingsHandler::getInstance();
  m_errorHandler = &ErrorHandler::getInstance();
  m_fromFilePath = fromFilePath;
  m_toFilePath = toFilePath;
  m_language = language;
  m_mode = mode;
}


DataHandler::~DataHandler() {}

// public slots ===============================================================

void DataHandler::run() {
  emit runned();
  if (!process()) emit failed();
  emit stopped();
}

// private methods ============================================================

bool DataHandler::process() {
  bool isError = true;
  QFile fromFile(m_fromFilePath);
  QFile toFile(m_toFilePath);
  QVector<DataRow*> originalRowsContainer;
  QVector<DataRow*> translatedRowsContainer;
  try {
    OpenFile(fromFile, QIODevice::ReadOnly);
    OpenFile(toFile, QIODevice::ReadWrite);

    if (fromFile.atEnd()) throw std::runtime_error("input file is empty");

    if (m_mode == MODE::BIN_TO_TEXT) {
      QDataStream from(&fromFile);
      QTextStream to(&toFile);
      toFile.resize(0); // clean output file
      if (!cryptProcessing(from, originalRowsContainer, PROCESS_MODE::DECRYPT)) {
        throw std::runtime_error("decrypt data was failed");
      }
      if (!textProcessing(to, originalRowsContainer, PROCESS_MODE::WRITE)) {
        throw std::runtime_error("write data to text stream was failed");
      }
    } else if (m_mode == MODE::TEXT_TO_BIN) {
      QTextStream from(&fromFile);
      QDataStream to(&toFile);
      toFile.resize(0);
      if (!textProcessing(from, originalRowsContainer, PROCESS_MODE::READ)) {
        throw std::runtime_error("read data from text stream was failed");
      }
      if (!cryptProcessing(to, originalRowsContainer, PROCESS_MODE::ENCRYPT)) {
        throw std::runtime_error("encrypt was failed");
      }
    } else if (m_mode == MODE::MERGE_BIN) {
      QDataStream from(&fromFile);
      QDataStream to(&toFile);
      if (!cryptProcessing(from, translatedRowsContainer, PROCESS_MODE::DECRYPT)) {
        throw std::runtime_error("decrypt data was failed");
      }
      if (!cryptProcessing(to, originalRowsContainer, PROCESS_MODE::DECRYPT)) {
        throw std::runtime_error("decrypt data was failed");
      }
      if (!mergeProcessing(translatedRowsContainer, originalRowsContainer)) {
        throw std::runtime_error("merge data was failed");
      }
      toFile.resize(0);
      if (!cryptProcessing(to, originalRowsContainer, PROCESS_MODE::ENCRYPT)) {
        throw std::runtime_error("encrypt data was failed");
      }
    } else if (m_mode == MODE::MERGE_TEXT) {
      QTextStream from(&fromFile);
      QTextStream to(&toFile);
      if (!textProcessing(from, translatedRowsContainer, PROCESS_MODE::READ)) {
        throw std::runtime_error("read data from text stream was failed");
      }
      if (!textProcessing(to, originalRowsContainer, PROCESS_MODE::READ)) {
        throw std::runtime_error("read data from text stream was failed");
      }
      if (!mergeProcessing(translatedRowsContainer, originalRowsContainer)) {
        throw std::runtime_error("merge data was failed");
      }
      toFile.resize(0);
      if (!textProcessing(to, originalRowsContainer, PROCESS_MODE::WRITE)) {
        throw std::runtime_error("write data to text stream was failed");
      }
    }

    isError = false;
  }
  catch (const std::runtime_error &err) {
    m_errorHandler->addErrorMessage("In function \"DataHandler::process\" " + QString(err.what()));
  }
  catch (...) {
    m_errorHandler->addErrorMessage("In function \"DataHandler::process\" processing data was failed.");
  }

  try {
    if (fromFile.isOpen()) CloseFile(fromFile);
    if (toFile.isOpen()) CloseFile(toFile);
  }
  catch (const std::runtime_error &err) {
    isError = true;
    m_errorHandler->addErrorMessage("In function \"DataHandler::process\" " + QString(err.what()));
  }

  deleteData(originalRowsContainer);
  deleteData(translatedRowsContainer);

  return !isError;
}

// ============================================================================

bool DataHandler::cryptProcessing(QDataStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode) {
  bool isError = false;
  QFile tmpFile(TMP_FILE_NAME);
  QDataStream tmp(&tmpFile);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite);

    if (mode == PROCESS_MODE::DECRYPT) {
      if (!compressProcessing(stream, tmp, mode)) throw std::runtime_error("uncompressing data was failed.");
      if (!binProcessing(tmp, data, PROCESS_MODE::READ)) throw std::runtime_error("reading data from bin stream was failed.");
    } else if (mode == PROCESS_MODE::ENCRYPT) {
      if (!binProcessing(tmp, data, PROCESS_MODE::WRITE)) throw std::runtime_error("writing data to bin stream was failed.");
      if (!compressProcessing(tmp, stream, mode)) throw std::runtime_error("compressing data was failed.");
    } else {
      throw std::runtime_error("unexpected compressing mode.");
    }
  }
  catch (const std::runtime_error &err) {
    isError = true;
    m_errorHandler->addErrorMessage("In function \"DataHandler::cryptProcessing\" " + QString(err.what()));
  }
  catch (...) {
    isError = true;
    m_errorHandler->addErrorMessage("In function \"DataHandler::cryptProcessing\" something went wrong.");
  }

  try {
    if (tmpFile.isOpen()) CloseFile(tmpFile);
    RemoveFile(tmpFile);
  }
  catch (const std::runtime_error &err) {
    isError = true;
    m_errorHandler->addErrorMessage("In function \"DataHandler::cryptProcessing\" " + QString(err.what()));
  }

  return !isError;
}

// ============================================================================

bool DataHandler::binProcessing(QDataStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode) {
  if (mode == PROCESS_MODE::READ) {
    emit started("READING BIN DATA");
  } else if (mode == PROCESS_MODE::WRITE) {
    emit started("WRITING BIN DATA");
  } else {
    return false;
  }

  bool isError = false;
  QThread thread;
  QTimer timer;
  BinDataProcessor processor(stream, data, mode);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &processor, SLOT(process()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  timer.setInterval(0);
  timer.moveToThread(&thread);
  processor.moveToThread(&thread);

  thread.start();

  // wait work complete and simultaneously get progress status
  do {
    emit progressed(processor.getProgress());
    if (processor.isError()) {
      isError = true;
      break;
    }
    Delay(10);
  } while (!processor.isComplete());

  thread.quit();
  thread.wait();

  return !isError;
}


bool DataHandler::textProcessing(QTextStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode) {
  if (mode == PROCESS_MODE::READ) {
    emit started("READING TEXT DATA");
  } else if (mode == PROCESS_MODE::WRITE) {
    emit started("WRITING TEXT DATA");
  } else {
    return false;
  }

  bool isError = false;
  QThread thread;
  QTimer timer;
  TextDataProcessor processor(stream, data, mode);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &processor, SLOT(process()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  timer.setInterval(0);
  timer.moveToThread(&thread);
  processor.moveToThread(&thread);

  thread.start();

  // wait work complete and simultaneously get progress status
  do {
    emit progressed(processor.getProgress());
    if (processor.isError()) {
      isError = true;
      break;
    }
    Delay(10);
  } while (!processor.isComplete());

  thread.quit();
  thread.wait();

  return !isError;
}

// ============================================================================

bool DataHandler::mergeProcessing(QVector<DataRow*>& from, QVector<DataRow*>& to) {
  emit started("MERGING DATA");

  std::sort(to.begin(), to.end(), [](DataRow *ptr1, DataRow *ptr2) -> bool { return *ptr1 < *ptr2; });

  bool isError = false;
  QTimer timer;
  QThread thread;
  MergeDataProcessor processor(from, to, m_language);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &processor, SLOT(process()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  timer.setInterval(0);
  timer.moveToThread(&thread);
  processor.moveToThread(&thread);
  thread.start();

  // wait work complete and simultaneously get progress status
  do {
    emit progressed(processor.getProgress());
    if (processor.isError()) {
      isError = true;
      break;
    }
    Delay(10);
  } while (!processor.isComplete());

  thread.quit();
  thread.wait();

  return !isError;
}

// ============================================================================

bool DataHandler::compressProcessing(QDataStream& from, QDataStream& to, PROCESS_MODE mode) {
  if (mode == PROCESS_MODE::DECRYPT) {
    emit started("UNCOMPRESSING BIN DATA");
  } else if (mode == PROCESS_MODE::ENCRYPT) {
    emit started("COMPRESSING BIN DATA");
  } else {
    return false;
  }

  bool isError = false;
  QTimer timer;
  QThread thread;
  DataCompressor compressor(from, to, mode);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &compressor, SLOT(process()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  compressor.init();
  timer.setInterval(0);
  timer.moveToThread(&thread);
  compressor.moveToThread(&thread);
  thread.start();

  // wait work complete and simultaneously get progress status
  do {
    emit progressed(compressor.getProgress());
    if (compressor.isError()) {
      isError = true;
      break;
    }
    Delay(10);
  } while (!compressor.isComplete());

  thread.quit();
  thread.wait();

  return !isError;
}

// ============================================================================

void DataHandler::deleteData(QVector<DataRow*>& dataRowsContainer) {
  for (int i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
  dataRowsContainer.clear();
}
