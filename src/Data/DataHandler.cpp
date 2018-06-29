#include <QtZlib/zlib.h>
#include "DataHandler.hpp"
#include "DataRow.hpp"


const char* TMP_FILE_NAME = "./data/tmp.bss";

// ============================================================================

DataHandler::DataHandler(const QString &fromFilePath, const QString &toFilePath, MODE mode) : QObject(nullptr) {
  settings = &Settings::getInstance();
  errorHandler = &ErrorHandler::getInstance();
  DataHandler::fromFilePath = fromFilePath;
  DataHandler::toFilePath = toFilePath;
  DataHandler::mode = mode;
}


DataHandler::~DataHandler() {}

// public slots ===============================================================

void DataHandler::start() {
  if (mode == MODE::BIN_TO_TEXT || mode == MODE::TEXT_TO_BIN) {
    if (!convertFile(fromFilePath, toFilePath, mode)) emit failed();
  } else if (mode == MODE::MERGE_TEXT || mode == MODE::MERGE_BIN) {
    if (!mergeFiles(fromFilePath, toFilePath, mode)) emit failed();
  }
  emit completed();
}


void DataHandler::stop() {}

// private methods ============================================================

bool DataHandler::mergeFiles(const QString &fromFilePath, const QString &toFilePath, MODE mode) {
  QFile fromFile(fromFilePath);
  QFile toFile(toFilePath);
  try {
    OpenFile(fromFile,  QIODevice::ReadOnly,  "DataHandler::mergeFiles()");
    OpenFile(toFile,    QIODevice::ReadWrite, "DataHandler::mergeFiles()");
    QVector<DataRow*> translatedRowsContainer;
    QVector<DataRow*> originalRowsContainer;

    if (mode == MODE::MERGE_BIN) {
      QDataStream from(&fromFile);
      QDataStream to(&toFile);
      readDataFromBinStream(from, translatedRowsContainer);
      readDataFromBinStream(to, originalRowsContainer);
      mergeData(translatedRowsContainer, originalRowsContainer);
      writeDataToBinStream(originalRowsContainer, to);
    }
    if (mode == MODE::MERGE_TEXT) {
      QTextStream from(&fromFile);
      QTextStream to(&toFile);
      readDataFromTextStream(from, translatedRowsContainer);
      readDataFromTextStream(to, originalRowsContainer);
      mergeData(translatedRowsContainer, originalRowsContainer);
      writeDataToTextStream(originalRowsContainer, to);
    }

    deleteData(translatedRowsContainer);
    deleteData(originalRowsContainer);

    CloseFile(fromFile, "DataHandler::convertFile()");
    CloseFile(toFile,   "DataHandler::convertFile()");
  }
  catch(...) {
    if (fromFile.isOpen()) CloseFile(fromFile, "DataHandler::mergeFiles()");
    if (toFile.isOpen())   CloseFile(toFile,   "DataHandler::mergeFiles()");
    return false;
  }
  return true;
}


//
bool DataHandler::convertFile(const QString &fromFilePath, const QString &toFilePath, MODE mode) {
  QFile fromFile(fromFilePath);
  QFile toFile(toFilePath);
  try {
    OpenFile(fromFile,  QIODevice::ReadOnly,  "DataHandler::convertFile()");
    OpenFile(toFile,    QIODevice::WriteOnly, "DataHandler::convertFile()");
    QVector<DataRow*> dataRowsContainer;

    if (mode == MODE::BIN_TO_TEXT) {
      QDataStream from(&fromFile);
      QTextStream to(&toFile);
      readDataFromBinStream(from, dataRowsContainer);
      writeDataToTextStream(dataRowsContainer, to);
    }
    if (mode == MODE::TEXT_TO_BIN) {
      QTextStream from(&fromFile);
      QDataStream to(&toFile);
      readDataFromTextStream(from, dataRowsContainer);
      writeDataToBinStream(dataRowsContainer, to);
    }

    deleteData(dataRowsContainer);

    CloseFile(fromFile,  "DataHandler::convertFile()");
    CloseFile(toFile, "DataHandler::convertFile()");
  }
  catch (...) {
    if (fromFile.isOpen())  CloseFile(fromFile, "DataHandler::convertFile()");
    if (toFile.isOpen()) CloseFile(toFile, "DataHandler::convertFile()");
    return false;
  }
  return true;
}

// ============================================================================

// read data rows from compressed input binary file
void DataHandler::readDataFromBinStream(QDataStream& from, QVector<DataRow*>& to) {
  try {
    decryptData(from, to);
  }
  catch (...) { throw; }
}


// write data rows to compressed output bin file
void DataHandler::writeDataToBinStream(QVector<DataRow*>& from, QDataStream& to) {
  try {
    to.device()->seek(0);
    encryptData(from, to);
  }
  catch (...) { throw; }
}


// read data rows from input text file
void DataHandler::readDataFromTextStream(QTextStream& from, QVector<DataRow*>& to) {
  try {
    from.setAutoDetectUnicode(true);
    from.skipWhiteSpace();
    while (true) {
      DataRow* dataRow = new DataRow();
      dataRow->readTextDataFrom(from);
      to.push_back(dataRow);
      if (from.atEnd()) break;
    }
  }
  catch (...) { throw; }
}


// write data rows to output text file
void DataHandler::writeDataToTextStream(QVector<DataRow*>& from, QTextStream& to) {
  try {
    to.device()->seek(0);
    to.setCodec("UTF-8");
    to.setGenerateByteOrderMark(true);
    for (int i = 0; i < from.size(); i++) {
      from[i]->writeTextDataTo(to);
    }
  }
  catch (...) { throw; }
}

// ============================================================================

void DataHandler::deleteData(QVector<DataRow*>& dataRowsContainer) {
  for (int i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
}


void DataHandler::mergeData(QVector<DataRow*>& from, QVector<DataRow*>& to) {
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
      } else if (*from.at(i) < *to.at(ind)) {
        end = ind;
      } else {
        beg = ind;
      }
    } while (beg != end);
  }
}

// decrypt data from input file to data container
void DataHandler::decryptData(QDataStream& from, QVector<DataRow*>& to) {
  QFile tmpFile(TMP_FILE_NAME);
  OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::decryptData()");
  QDataStream tmp(&tmpFile);

  uncompressData(from, tmp);

  tmp.device()->seek(0); // set pos to file begin

  try {
    // decrypting uncompressed data
    while (true) {
      DataRow* dataRow = new DataRow();
      dataRow->readBinDataFrom(tmp);
      to.push_back(dataRow);
      if (tmp.atEnd()) break;
    }
  }
  catch (...) {
    errorHandler->addException("In function \"DataHandler::decryptData()\" read data was failed.");
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::decryptData()");
    RemoveFile(tmpFile, "DataHandler::decryptData()");
    throw false;
  }
  CloseFile(tmpFile, "DataHandler::decryptData()");
  RemoveFile(tmpFile, "DataHandler::decryptData()");
}


// uncompress data from input file to tmp data file
void DataHandler::uncompressData(QDataStream& from, QDataStream& to) {
  unsigned long compressedDataSize = 0;
  unsigned long uncompressedDataSize = 0;
  int ulSize = static_cast<int>(sizeof(uint32_t)); // guaranteed 4 bytes length for unsigned long
  int dataLength = 0;

  dataLength = static_cast<int>(from.device()->size());
  compressedDataSize = static_cast<unsigned long>(dataLength - ulSize); // 1st 4 bytes holds information about uncompressed data size

  ReadDataFromStream(from, uncompressedDataSize, ulSize, "DataHandler::uncompressData()");

  uint8_t *inBuff = nullptr;
  uint8_t *outBuff = nullptr;
  try {
    inBuff = new uint8_t[compressedDataSize];
    outBuff = new uint8_t[uncompressedDataSize];
    ReadDataFromStream(from, *inBuff, compressedDataSize, "DataHandler::uncompressData()");
  }
  catch (...) {
    if (inBuff) delete[] inBuff;
    if (outBuff) delete[] outBuff;
    errorHandler->addException("In function \"DataHandler::uncompressData()\" allocated memory was failed.");
    throw false;
  }

  int result = uncompress(outBuff, &uncompressedDataSize, inBuff, compressedDataSize);

  if (inBuff) delete[] inBuff;
  if (result == Z_OK) {
    WriteDataToStream(to, *outBuff, uncompressedDataSize, "DataHandler::uncompressData()");
    if (outBuff) delete[] outBuff;
  } else {
    if (outBuff) delete[] outBuff;
    errorHandler->addException("In function \"DataHandler::uncompressData()\" uncompress was failed.");
    throw false;
  }
}


// encrypt data to output binary file from data container
void DataHandler::encryptData(QVector<DataRow*>& from, QDataStream& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::encryptData()");
    QDataStream tmp(&tmpFile);

    // write data rows to uncompressed tmp data file
    for (int i = 0; i < from.size(); i++) {
      from[i]->writeBinDataTo(tmp);
    }

    tmp.device()->seek(0); // set pos to file begin

    compressData(tmp, to); // compress tmp data file to output file
  }
  catch (...) {
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::encryptData()");
    RemoveFile(tmpFile, "DataHandler::encryptData()");
    throw false;
  }
  CloseFile(tmpFile, "DataHandler::encryptData()");
  RemoveFile(tmpFile, "DataHandler::encryptData()");
}


//
void DataHandler::compressData(QDataStream& from, QDataStream& to) {
  unsigned long uncompressedDataSize = 0;
  unsigned long compressedDataSize = 0;
  int ulSize = static_cast<int>(sizeof(uint32_t)); // guaranteed 4 bytes length for unsigned long

  uncompressedDataSize = static_cast<int>(from.device()->size());
  compressedDataSize = compressBound(uncompressedDataSize);

  uint8_t *inBuff = nullptr;
  uint8_t *outBuff = nullptr;
  try {
    inBuff = new uint8_t[uncompressedDataSize];
    outBuff = new uint8_t[compressedDataSize];
  }
  catch (...) {
    if (inBuff) delete[] inBuff;
    if (outBuff) delete[] outBuff;
    errorHandler->addException("In function \"DataHandler::compressData()\" allocated memory was failed.");
    throw false;
  }

  try {
    ReadDataFromStream(from, *inBuff, uncompressedDataSize, "DataHandler::compressData()");
    int level = settings->getSetting("", "compressing_level", 1).toInt();
    int result = compress2(outBuff, &compressedDataSize, inBuff, uncompressedDataSize, level);

    if (inBuff) delete[] inBuff;
    if (result != Z_OK) {
      if (outBuff) delete[] outBuff;
      throw false;
    }
    WriteDataToStream(to, uncompressedDataSize, ulSize, "DataHandler::compressData()");
    WriteDataToStream(to, *outBuff, static_cast<int>(compressedDataSize), "DataHandler::compressData()");
    if (outBuff) delete[] outBuff;
  }
  catch (...) {
    errorHandler->addException("In function \"DataHandler::compressData()\" compressing was failed.");
    throw false;
  }
}
