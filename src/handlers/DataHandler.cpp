#include <QtZlib/zlib.h>
#include "DataHandler.hpp"
#include "DataRow.hpp"


const char* TMP_FILE_NAME = "./data/tmp.bss";

// ============================================================================

DataHandler::DataHandler(const QString &fromFilePath, const QString &toFilePath, MODE mode) : QObject(nullptr) {
  settingsHandler = &SettingsHandler::getInstance();
  errorHandler = &ErrorHandler::getInstance();
  DataHandler::fromFilePath = fromFilePath;
  DataHandler::toFilePath = toFilePath;
  DataHandler::mode = mode;
}


DataHandler::~DataHandler() {}

// public slots ===============================================================

void DataHandler::start() {
  if (!process(fromFilePath, toFilePath, mode)) emit failed();
  emit completed();
}


void DataHandler::stop() {}

// private methods ============================================================

//
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
      readDataFromBinStream(from, originalRowsContainer);
      toFile.resize(0); // clean output file
      writeDataToTextStream(originalRowsContainer, to);
    } else if (mode == MODE::TEXT_TO_BIN) {
      QTextStream from(&fromFile);
      QDataStream to(&toFile);
      readDataFromTextStream(from, originalRowsContainer);
      toFile.resize(0);
      writeDataToBinStream(originalRowsContainer, to);
    } else if (mode == MODE::MERGE_BIN) {
      QDataStream from(&fromFile);
      QDataStream to(&toFile);
      readDataFromBinStream(from, translatedRowsContainer);
      readDataFromBinStream(to, originalRowsContainer);
      mergeData(translatedRowsContainer, originalRowsContainer);
      toFile.resize(0);
      writeDataToBinStream(originalRowsContainer, to);
    } else if (mode == MODE::MERGE_TEXT) {
      QTextStream from(&fromFile);
      QTextStream to(&toFile);
      readDataFromTextStream(from, translatedRowsContainer);
      readDataFromTextStream(to, originalRowsContainer);
      mergeData(translatedRowsContainer, originalRowsContainer);
      toFile.resize(0);
      writeDataToTextStream(originalRowsContainer, to);
    }

    isError = false;
  }
  catch (const std::runtime_error &err) {
    errorHandler->addErrorMessage("In function \"DataHandler::process\" " + QString(err.what()));
  }
  catch (...) {
    errorHandler->addErrorMessage("In function \"DataHandler::process\" something went wrong.");
  }

  try {
    if (fromFile.isOpen()) CloseFile(fromFile);
    if (toFile.isOpen()) CloseFile(toFile);
  }
  catch (const std::runtime_error &err) {
    isError = true;
    errorHandler->addErrorMessage("In function \"DataHandler::process\" " + QString(err.what()));
  }

  deleteData(originalRowsContainer);
  deleteData(translatedRowsContainer);

  return !isError;
}

// ============================================================================

// read data rows from compressed input binary file
void DataHandler::readDataFromBinStream(QDataStream& from, QVector<DataRow*>& to) {
  from.device()->reset();
  from.resetStatus();
  if (!decryptData(from, to)) throw std::runtime_error("read data from bin stream was failed.");
}


// write data rows to compressed output bin file
void DataHandler::writeDataToBinStream(QVector<DataRow*>& from, QDataStream& to) {
  to.device()->reset();
  to.resetStatus();
  if (!encryptData(from, to)) throw std::runtime_error("write data to bin stream was failed.");
}


// read data rows from input text file
void DataHandler::readDataFromTextStream(QTextStream& from, QVector<DataRow*>& to) {
  from.device()->seek(0);
  from.resetStatus();
  from.setAutoDetectUnicode(true);
  from.skipWhiteSpace();
  try {
    while (true) {
      DataRow* dataRow = new DataRow();
      if (!dataRow->readTextDataFrom(from)) throw false;
      to.push_back(dataRow);
      if (from.atEnd()) break;
    }
  }
  catch (std::bad_alloc) {
    errorHandler->addErrorMessage("In function \"DataHandler::readDataFromTextStream\" allocating memory was failed.");
    throw std::runtime_error("read data from text stream was failed.");
  }
  catch (...) {
    throw std::runtime_error("read data from text stream was failed.");
  }
}


// write data rows to output text file
void DataHandler::writeDataToTextStream(QVector<DataRow*>& from, QTextStream& to) {
  to.device()->seek(0);
  to.resetStatus();
  to.setCodec("UTF-8");
  to.setGenerateByteOrderMark(true);
  try {
    for (int i = 0; i < from.size(); i++) {
      if (!from[i]->writeTextDataTo(to)) throw false;
    }
  }
  catch (...) {
    throw std::runtime_error("write data to text stream was failed.");
  }
}


void DataHandler::mergeData(QVector<DataRow*>& from, QVector<DataRow*>& to) {
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
    throw std::runtime_error("merge data was failed.");
  }
}

// ============================================================================

void DataHandler::deleteData(QVector<DataRow*>& dataRowsContainer) {
  for (int i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
}

// ============================================================================

// decrypt data from input file to data container
bool DataHandler::decryptData(QDataStream& from, QVector<DataRow*>& to) {
  bool isError = true;
  QFile tmpFile(TMP_FILE_NAME);
  QDataStream tmp(&tmpFile);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite);
    if (!uncompressData(from, tmp)) throw std::runtime_error("uncompressing data was failed.");
    tmp.device()->reset();
    tmp.resetStatus();
    while (true) {
      DataRow* dataRow = new DataRow();
      if (!dataRow->readBinDataFrom(tmp)) throw std::ios_base::failure("read data was failed.");
      to.push_back(dataRow);
      if (tmp.atEnd()) break;
    }
    isError = false;
  }
  catch (const std::runtime_error &err) {
    errorHandler->addErrorMessage("In function \"DataHandler::decryptData\" " + QString(err.what()));
  }
  catch (...) {
    errorHandler->addErrorMessage("In function \"DataHandler::decryptData\" something went wrong.");
  }

  try {
    if (tmpFile.isOpen()) CloseFile(tmpFile);
    RemoveFile(tmpFile);
  }
  catch (const std::runtime_error &err) {
    isError = true;
    errorHandler->addErrorMessage("In function \"DataHandler::decryptData\" " + QString(err.what()));
  }

  return !isError;
}


// decompress data from input file to tmp data file
bool DataHandler::uncompressData(QDataStream& from, QDataStream& to) {
  bool isError = true;
  unsigned long expectedUncompressedDataSize = 0;
  unsigned long uncompressedDataSize = 0;
  unsigned int BUFF_SIZE = 16384; // TODO: change buffer size
  uint8_t *inBuff = nullptr;
  uint8_t *outBuff = nullptr;
  z_stream stream = { 0 };
  try {
    inBuff = new uint8_t[BUFF_SIZE];
    outBuff = new uint8_t[BUFF_SIZE];
    ReadDataFromStream(from, expectedUncompressedDataSize, 4); // read uncompressed data size from input file
    int result = inflateInit(&stream);
    if (result != Z_OK) throw std::runtime_error("inflate init was failed.");
    do {
      result = ReadDataFromStream(from, *inBuff, BUFF_SIZE); // number of bytes available at next_in
      stream.avail_in = static_cast<unsigned int>(result); // negative value get throw in read function
      stream.next_in = inBuff; // next input byte
      if (stream.avail_in == 0) break;
      do {
        stream.avail_out = BUFF_SIZE; // remaining free space at next_out
        stream.next_out = outBuff; // next output byte should be put there
        result = inflate(&stream, Z_NO_FLUSH); // decompress data
        if (result != Z_OK && result != Z_STREAM_END) throw std::runtime_error("inflate was failed.");
        int have = BUFF_SIZE - stream.avail_out; // decompressed data size
        uncompressedDataSize += have;
        if (have > 0) WriteDataToStream(to, *outBuff, have); // write decompressed data to out file
      } while (stream.avail_out == 0);
    } while (result != Z_STREAM_END);
    if (uncompressedDataSize != expectedUncompressedDataSize) throw std::runtime_error("bad decompressed data length.");
    isError = false;
  }
  catch (const std::runtime_error &err) {
    errorHandler->addErrorMessage("In function \"DataHandler::uncompressData\" " + QString(err.what()));
  }
  catch (std::bad_alloc) {
    errorHandler->addErrorMessage("In function \"DataHandler::uncompressData\" allocating memory was failed.");
  }
  catch (...) {
    errorHandler->addErrorMessage("In function \"DataHandler::uncompressData\" something went wrong.");
  }

  inflateEnd(&stream);
  if (inBuff) delete[] inBuff;
  if (outBuff) delete[] outBuff;

  return !isError;
}

// ============================================================================

// encrypt data to output binary file from data container
bool DataHandler::encryptData(QVector<DataRow*>& from, QDataStream& to) {
  bool isError = true;
  QFile tmpFile(TMP_FILE_NAME);
  QDataStream tmp(&tmpFile);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite);
    for (int i = 0; i < from.size(); i++) {
      if (!from[i]->writeBinDataTo(tmp)) throw std::ios_base::failure("write data was failed.");
    }
    tmp.device()->reset();
    tmp.resetStatus();
    if (!compressData(tmp, to)) throw std::runtime_error("compressing data was failed.");
    isError = false;
  }
  catch (const std::runtime_error &err) {
    errorHandler->addErrorMessage("In function \"DataHandler::encryptData\" " + QString(err.what()));
  }
  catch (...) {
    errorHandler->addErrorMessage("In function \"DataHandler::encryptData\" something went wrong.");
  }

  try {
    if (tmpFile.isOpen()) CloseFile(tmpFile);
    RemoveFile(tmpFile);
  }
  catch (const std::runtime_error &err) {
    isError = true;
    errorHandler->addErrorMessage("In function \"DataHandler::encryptData\" " + QString(err.what()));
  }

  return !isError;
}


// compress binary tmp data file to binary output file
bool DataHandler::compressData(QDataStream& from, QDataStream& to) {
  bool isError = true;
  unsigned long uncompressedDataSize = 0;
  unsigned int BUFF_SIZE = 16384; // TODO: change buffer size
  uint8_t *inBuff = nullptr;
  uint8_t *outBuff = nullptr;
  z_stream stream = { 0 };
  int flush, result;
  try {
    inBuff = new uint8_t[BUFF_SIZE];
    outBuff = new uint8_t[BUFF_SIZE];
    uncompressedDataSize = static_cast<unsigned long>(from.device()->size());
    WriteDataToStream(to, uncompressedDataSize, 4);
    int level = settingsHandler->getSetting("", "compressing_level", 1).toInt();
    if (deflateInit(&stream, level) != Z_OK) throw std::runtime_error("deflate init was failed.");
    do {
      stream.avail_in = static_cast<unsigned int>(ReadDataFromStream(from, *inBuff, static_cast<int>(BUFF_SIZE)));
      stream.next_in = inBuff;
      flush = (from.device()->atEnd()) ? Z_FINISH : Z_NO_FLUSH;
      do {
        stream.avail_out = BUFF_SIZE; // remaining free space at next_out
        stream.next_out = outBuff; // next output byte should be put there
        result = deflate(&stream, flush);
        if (result == Z_STREAM_ERROR || result == Z_BUF_ERROR) throw std::runtime_error("deflate was failed.");
        int have = static_cast<int>(BUFF_SIZE - stream.avail_out); // compressed data size on current iteration
        if (have > 0) WriteDataToStream(to, *outBuff, have);
      } while (stream.avail_out == 0);
    } while (flush != Z_FINISH);
    if (result != Z_STREAM_END) throw std::runtime_error("compressed was failed.");
    isError = false;
  }
  catch (const std::runtime_error &err) {
    errorHandler->addErrorMessage("In function \"DataHandler::compressData\" " + QString(err.what()));
  }
  catch (std::bad_alloc) {
    errorHandler->addErrorMessage("In function \"DataHandler::compressData\" allocating memory was failed.");
  }
  catch (...) {
    errorHandler->addErrorMessage("In function \"DataHandler::compressData\" something went wrong.");
  }

  deflateEnd(&stream);
  if (inBuff) delete[] inBuff;
  if (outBuff) delete[] outBuff;

  return !isError;
}
