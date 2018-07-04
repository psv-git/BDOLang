#include "DataHandler.hpp"
#include "TextDataReader.hpp"
#include "TextDataWriter.hpp"
#include "BinDataWriter.hpp"
#include "DataCompressor.hpp"


const char* TMP_FILE_NAME = "./data/tmp.bss";

// ============================================================================

DataHandler::DataHandler(const QString &fromFilePath, const QString &toFilePath, MODE mode) {
  m_settingsHandler = &SettingsHandler::getInstance();
  m_errorHandler = &ErrorHandler::getInstance();
  m_fromFilePath = fromFilePath;
  m_toFilePath = toFilePath;
  m_mode = mode;
}


DataHandler::~DataHandler() {}

// public slots ===============================================================

void DataHandler::run() {
  emit runned();
  if (!process(m_fromFilePath, m_toFilePath, m_mode)) emit failed();
  emit stopped();
}

// private methods ============================================================

bool DataHandler::process(const QString &fromFilePath, const QString &toFilePath, MODE mode) {
  bool isError = true;
  QFile fromFile(fromFilePath);
  QFile toFile(toFilePath);
  QVector<DataRow*> originalRowsContainer;
  QVector<DataRow*> translatedRowsContainer;
  try {
    OpenFile(fromFile, QIODevice::ReadOnly);
    OpenFile(toFile, QIODevice::ReadWrite);

    if (mode == MODE::BIN_TO_TEXT) {
      QDataStream from(&fromFile);
      QTextStream to(&toFile);
      toFile.resize(0); // clean output file
      if (!decryptData(from, originalRowsContainer)) throw std::runtime_error("decrypt data was failed");
      if (!writeDataToTextStream(originalRowsContainer, to)) throw std::runtime_error("write data to text stream was failed");
    } else if (mode == MODE::TEXT_TO_BIN) {
      QTextStream from(&fromFile);
      QDataStream to(&toFile);
      toFile.resize(0); // clean output file
      if (!readDataFromTextStream(from, originalRowsContainer)) throw std::runtime_error("read data from text stream was failed");
      if (!encryptData(originalRowsContainer, to)) throw std::runtime_error("encrypt was failed");
    } else if (mode == MODE::MERGE_BIN) {
      QDataStream from(&fromFile);
      QDataStream to(&toFile);
      if (!decryptData(from, translatedRowsContainer)) throw std::runtime_error("decrypt data was failed");
      if (!decryptData(to, originalRowsContainer)) throw std::runtime_error("decrypt data was failed");
      if (!mergeData(translatedRowsContainer, originalRowsContainer)) throw std::runtime_error("merge data was failed");
      toFile.resize(0);
      if (!encryptData(originalRowsContainer, to)) throw std::runtime_error("encrypt data was failed");
    } else if (mode == MODE::MERGE_TEXT) {
      QTextStream from(&fromFile);
      QTextStream to(&toFile);
      if (!readDataFromTextStream(from, translatedRowsContainer)) throw std::runtime_error("read data from text stream was failed");
      if (!readDataFromTextStream(to, originalRowsContainer)) throw std::runtime_error("read data from text stream was failed");
      if (!mergeData(translatedRowsContainer, originalRowsContainer)) throw std::runtime_error("merge data was failed");
      toFile.resize(0);
      if (!writeDataToTextStream(originalRowsContainer, to)) throw std::runtime_error("write data to text stream was failed");
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

// read data from .loc file to data container
bool DataHandler::cryptData(QDataStream& from, QVector<DataRow*>& to, PROCESS_MODE mode) {
  bool isError = false;
  QFile tmpFile(TMP_FILE_NAME);
  QDataStream tmp(&tmpFile);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite);

    if (mode == PROCESS_MODE::DECRYPT) {
      if (!processData(from, tmp, PROCESS_MODE::DECRYPT)) throw std::runtime_error("uncompressing data was failed.");
      if (!readDataFromBinStream(tmp, to)) throw std::runtime_error("reading bin data from stream was failed.");
    }
    if (mode == PROCESS_MODE::ENCRYPT) {
      if (!writeDataToBinStream(from, tmp)) throw std::runtime_error("writing bin data to stream was failed.");
      if (!processData(tmp, to, PROCESS_MODE::ENCRYPT)) throw std::runtime_error("compressing data was failed.");
    }
  }
  catch (const std::runtime_error &err) {
    isError = true;
    m_errorHandler->addErrorMessage("In function \"DataHandler::decryptData\" " + QString(err.what()));
  }
  catch (...) {
    isError = true;
    m_errorHandler->addErrorMessage("In function \"DataHandler::decryptData\" something went wrong.");
  }

  try {
    if (tmpFile.isOpen()) CloseFile(tmpFile);
    RemoveFile(tmpFile);
  }
  catch (const std::runtime_error &err) {
    isError = true;
    m_errorHandler->addErrorMessage("In function \"DataHandler::decryptData\" " + QString(err.what()));
  }

  return !isError;
}

// ============================================================================

bool DataHandler::readDataFromBinStream(QDataStream& from, QVector<DataRow*>& to) {
//  tmp.device()->reset();
//    tmp.resetStatus();
//    while (true) {
//      DataRow* dataRow = new DataRow();
//      dataRow->readBinDataFrom(tmp);
//      to.push_back(dataRow);
//      if (tmp.atEnd()) break;
//    }
//    isError = false;
}


bool DataHandler::writeDataToBinStream(QVector<DataRow*>& from, QDataStream& to) {
  emit started("WRITING BIN DATA");
  bool isError = false;
  QTimer timer;
  QThread thread;
  BinDataWriter writer(from, to);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &writer, SLOT(write()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  timer.setInterval(0);
  timer.moveToThread(&thread);
  writer.moveToThread(&thread);

  thread.start();

  // wait work complete and simultaneously get progress status
  do {
    emit progressed(writer.getProgress());
    if (writer.isError()) {
      isError = true;
      break;
    }
    Delay(10);
  } while (!writer.isComplete());

  thread.quit();
  thread.wait();

  return !isError;
}


bool DataHandler::readDataFromTextStream(QTextStream& from, QVector<DataRow*>& to) {
  emit started("READING TEXT DATA");
  bool isError = false;
  QThread thread;
  QTimer timer;
  TextDataReader reader(from, to);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &reader, SLOT(read()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  timer.setInterval(0);
  timer.moveToThread(&thread);
  reader.moveToThread(&thread);

  thread.start();

  // wait work complete and simultaneously get progress status
  do {
    emit progressed(reader.getProgress());
    if (reader.isError()) {
      isError = true;
      break;
    }
    Delay(10);
  } while (!reader.isComplete());

  thread.quit();
  thread.wait();

  return !isError;
}


bool DataHandler::writeDataToTextStream(QVector<DataRow*>& from, QTextStream& to) {
  emit started("WRITING TEXT DATA");
  bool isError = false;
  QTimer timer;
  QThread thread;
  TextDataWriter writer(from, to);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &writer, SLOT(write()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  timer.setInterval(0);
  timer.moveToThread(&thread);
  writer.moveToThread(&thread);

  thread.start();

  // wait work complete and simultaneously get progress status
  do {
    emit progressed(writer.getProgress());
    if (writer.isError()) {
      isError = true;
      break;
    }
    Delay(10);
  } while (!writer.isComplete());

  thread.quit();
  thread.wait();

  return !isError;
}


bool DataHandler::mergeData(QVector<DataRow*>& from, QVector<DataRow*>& to) {
  emit started("MERGING DATA");
  try {
    std::sort(to.begin(), to.end(), [](DataRow *ptr1, DataRow *ptr2) -> bool { return *ptr1 < *ptr2; }); // sorting rows by [sheet, id1, id2, id3, id4]
    // save sheets ranges
    QMap<unsigned long, QPair<int, int>> sheetsPositionsList; // [sheet, <begin index, end index>]
    unsigned long sheetValue;
    int beg = 0, end = 0;
    sheetValue = to.at(beg)->getSheet();
    for (beg, end; end < to.size(); end++) {
      if (sheetValue != to.at(end)->getSheet()) {
        sheetsPositionsList.insert(sheetValue, qMakePair(beg, end));
        beg = end;
      }
      sheetValue = to.at(beg)->getSheet();
    }
    sheetsPositionsList.insert(sheetValue, qMakePair(beg, end));
    // get translated row and replace original row, if it was finded
    // if original row was not finded - translated row will skiped
    for (int i = 0; i < from.size(); i++) {
      sheetValue = from.at(i)->getSheet();
      QPair<int, int> indexes = sheetsPositionsList.value(sheetValue, qMakePair(0, to.size()));
      beg = indexes.first;
      end = indexes.second;
      do {
        int ind = beg + (end - beg) / 2;
        if (*from.at(i) == *to.at(ind)) {
          to[ind]->setString(from.at(i)->getString());
          break;
        }
        if (*from.at(i) < *to.at(ind)) end = ind;
        else beg = ind;
      } while (beg != end);
    }
  }
  catch (...) {
    throw std::runtime_error("merging data was failed.");
  }
  return true;
}

// ============================================================================

bool DataHandler::compressProcessing(QDataStream& from, QDataStream& to, PROCESS_MODE mode) {
  bool isError = false;
  QTimer timer;
  QThread thread;
  DataCompressor compressor(from, to, mode);

  connect(&thread, SIGNAL(started()), &timer, SLOT(start()));
  connect(&timer, SIGNAL(timeout()), &compressor, SLOT(process()));
  connect(&thread, SIGNAL(finished()), &timer, SLOT(stop()));

  if (mode == PROCESS_MODE::DECRYPT) {
    emit started("UNCOMPRESSING BIN DATA");
  }
  if (mode == PROCESS_MODE::ENCRYPT) {
    emit started("COMPRESSING BIN DATA");
  }

  compressor.init()
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
}
