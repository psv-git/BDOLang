#include "DataHandler.hpp"
#include "DataRow.hpp"

namespace zlib {
#include <zlib.h>
}


DataHandler::DataHandler() {}


DataHandler::~DataHandler() {
  resetData();
}

// public methods =============================================================

void DataHandler::mergeFiles(const QString &fromFilePath, const QString &toFilePath, MODE mode) {
  QFile fromFile(fromFilePath);
  QFile toFile(toFilePath);
  try {
    OpenFile(fromFile,  QIODevice::ReadOnly, "DataHandler::mergeFiles()");
    OpenFile(toFile, QIODevice::ReadWrite, "DataHandler::mergeFiles()");

    if (mode == MODE::MERGE_TEXT) {
      QTextStream from(&fromFile);
      from.setAutoDetectUnicode(true);
      from.skipWhiteSpace();
      QTextStream to(&toFile);
      to.setAutoDetectUnicode(true);
      to.skipWhiteSpace();
      to.setCodec("UTF-8");
      to.setGenerateByteOrderMark(true);

      readDataFromTextStream(to, mode); // save data; now we may rewrite file
      to.device()->seek(0);             // back to begin file

      std::sort(dataRowsContainer.begin(), dataRowsContainer.end(), [](DataRow *ptr1, DataRow *ptr2) -> bool { return *ptr1 < *ptr2; }); // sorting dataRows by [sheet, id1, id2, id3, id4]

      // save sheets range
      QMap<unsigned long, QPair<int, int>> sheetsPositionsList; // [sheet, <begin index, end index>]
      unsigned long sheetValue;
      for (int beg = 0, end = 0; end < dataRowsContainer.size(); end++) {
        sheetValue = dataRowsContainer.at(beg)->getSheet();
        if (sheetValue != dataRowsContainer.at(end)->getSheet()) {
          sheetsPositionsList.insert(sheetValue, qMakePair(beg, end));
          beg = end;
        }
      }

      while (true) {
        DataRow* dataRow = new DataRow();
        dataRow->readTextDataFrom(from, mode);
        sheetValue = dataRow->getSheet();
        QPair<int, int> indexes = sheetsPositionsList.value(sheetValue, qMakePair(0, dataRowsContainer.size()));
        for (int i = indexes.first; i < indexes.second; i++) { // from begin sheet index to end sheet index
          if (*dataRow == *dataRowsContainer.at(i)) {
            dataRowsContainer.at(i)->setString(dataRow->getString());
            break;
          }
        }
        delete dataRow;
        if (from.atEnd()) break;
      }

      writeDataToTextStream(to);
    }

    CloseFile(fromFile,  "DataHandler::convertFile()");
    CloseFile(toFile, "DataHandler::convertFile()");
  }
  catch(...) {
    if (fromFile.isOpen())  CloseFile(fromFile,  "DataHandler::mergeFiles()");
    if (toFile.isOpen()) CloseFile(toFile, "DataHandler::mergeFiles()");
    throw;
  }
}


//
void DataHandler::convertFile(const QString &fromFilePath, const QString &toFilePath, MODE mode) {
  QFile fromFile(fromFilePath);
  QFile toFile(toFilePath);
  try {
    OpenFile(fromFile,  QIODevice::ReadOnly, "DataHandler::convertFile()");
    OpenFile(toFile, QIODevice::WriteOnly, "DataHandler::convertFile()");

    if (mode == MODE::BIN_TO_TEXT) {
      QDataStream from(&fromFile);
      QTextStream to(&toFile);
      to.setCodec("UTF-8");
      to.setGenerateByteOrderMark(true);
      readDataFromBinStream(from);
      writeDataToTextStream(to);
    } else if (mode == MODE::TEXT_TO_BIN) {
      QTextStream from(&fromFile);
      QDataStream to(&toFile);
      from.setAutoDetectUnicode(true);
      from.skipWhiteSpace();
      readDataFromTextStream(from, mode);
      writeDataToBinStream(to);
    }

    CloseFile(fromFile,  "DataHandler::convertFile()");
    CloseFile(toFile, "DataHandler::convertFile()");
  }
  catch (...) {
    if (fromFile.isOpen())  CloseFile(fromFile,  "DataHandler::convertFile()");
    if (toFile.isOpen()) CloseFile(toFile, "DataHandler::convertFile()");
    throw;
  }
}

// PRIVATE METHODS ============================================================

// delete existed data
void DataHandler::resetData() {
  for (int i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
  dataRowsContainer.clear();
}


// read data rows from compressed input binary file
void DataHandler::readDataFromBinStream(QDataStream& from) {
  try {
    decrypt(from, dataRowsContainer);
  }
  catch (...) { throw; }
}


// write data rows to compressed output bin file
void DataHandler::writeDataToBinStream(QDataStream& to) {
  try {
    encrypt(dataRowsContainer, to);
  }
  catch (...) { throw; }
}


// read data rows from input text file
void DataHandler::readDataFromTextStream(QTextStream& from, MODE mode) {
  try {
    while (true) {
      DataRow* dataRow = new DataRow();
      dataRow->readTextDataFrom(from, mode);
      dataRowsContainer.push_back(dataRow);
      if (from.atEnd()) break;
    }
  }
  catch (...) { throw; }
}


// write data rows to output text file
void DataHandler::writeDataToTextStream(QTextStream& to) {
  try {
    for (int i = 0; i < dataRowsContainer.size(); i++) {
      dataRowsContainer[i]->writeTextDataTo(to);
    }
  }
  catch (...) { throw; }
}

// ============================================================================

// decrypt data from input file to data container
void DataHandler::decrypt(QDataStream& from, QVector<DataRow*>& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::decrypt()");
    QDataStream tmp(&tmpFile);

    uncompress(from, tmp);

    tmp.device()->seek(0); // set pos to file begin

    // decrypting uncompressed data
    while (true) {
      DataRow* dataRow = new DataRow();
      dataRow->readBinDataFrom(tmp);
      to.push_back(dataRow);
      if (tmp.atEnd()) break;
    }
  }
  catch (...) {
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::decrypt()");
    RemoveFile(tmpFile, "DataHandler::decrypt()");
    throw;
  }
  CloseFile(tmpFile,  "DataHandler::decrypt()");
  RemoveFile(tmpFile, "DataHandler::decrypt()");
}


// uncompress data from input file to tmp data file
void DataHandler::uncompress(QDataStream& from, QDataStream& to) {
  unsigned long compressedDataSize   = 0;
  unsigned long uncompressedDataSize = 0;
  size_t ulSize      = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long
  size_t dataLength  = 0;

  dataLength         = from.device()->size();
  compressedDataSize = dataLength - ulSize; // 1st 4 bytes holds information about uncompressed data size

  ReadDataFromStream(from, uncompressedDataSize, ulSize, "DataHandler::uncompress()");

  uint8_t *inBuff  = nullptr;
  uint8_t *outBuff = nullptr;
  try {
    inBuff = new uint8_t[compressedDataSize];
    outBuff = new uint8_t[uncompressedDataSize];
    ReadDataFromStream(from, *inBuff, compressedDataSize, "DataHandler::uncompress()");
  }
  catch (...) {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::uncompress()\" allocated memory was failed.");
    throw;
  }

  int result = zlib::uncompress(outBuff, &uncompressedDataSize, inBuff, compressedDataSize);

  if (inBuff) delete[] inBuff;
  if (result == Z_OK) {
    WriteDataToStream(to, *outBuff, uncompressedDataSize, "DataHandler::uncompress()");
    if (outBuff) delete[] outBuff;
  } else {
    if (outBuff) delete[] outBuff;
    AddException("In function \"uncompress()\" uncompress was failed.");
    throw;
  }
}

// ============================================================================

// encrypt data to output binary file from data container
void DataHandler::encrypt(QVector<DataRow*>& from, QDataStream& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::encrypt()");
    QDataStream tmp(&tmpFile);

    // write data rows to uncompressed tmp data file
    for (int i = 0; i < from.size(); i++) {
      from[i]->writeBinDataTo(tmp);
    }

    tmp.device()->seek(0); // set pos to file begin

    compress(tmp, to); // compress tmp data file to output file
  }
  catch (...) {
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::encrypt()");
    RemoveFile(tmpFile, "DataHandler::encrypt()");
    throw;
  }
  CloseFile(tmpFile,  "DataHandler::encrypt()");
  RemoveFile(tmpFile, "DataHandler::encrypt()");
}


//
void DataHandler::compress(QDataStream& from, QDataStream& to) {
  unsigned long uncompressedDataSize = 0;
  unsigned long compressedDataSize   = 0;
  size_t ulSize = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long

  uncompressedDataSize = from.device()->size();
  compressedDataSize   = zlib::compressBound(uncompressedDataSize);

  uint8_t *inBuff  = nullptr;
  uint8_t *outBuff = nullptr;
  try {
    inBuff = new uint8_t[uncompressedDataSize];
    outBuff = new uint8_t[compressedDataSize];
    ReadDataFromStream(from, *inBuff, uncompressedDataSize, "DataHandler::compress()");
  }
  catch (...) {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::compress()\" allocated memory was failed.");
    throw;
  }

  int result = zlib::compress2(outBuff, &compressedDataSize, inBuff, uncompressedDataSize, Z_BEST_SPEED);

  if (inBuff)  delete[] inBuff;
  if (result == Z_OK) {
    WriteDataToStream(to, uncompressedDataSize, ulSize, "DataHandler::compress()");
    WriteDataToStream(to, *outBuff, compressedDataSize, "DataHandler::compress()");
    if (outBuff) delete[] outBuff;
  } else {
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::compress()\" compress was failed.");
    throw;
  }
}
