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
    OpenFile(fromFile,  QIODevice::ReadOnly, "DataHandler::mergeTextFiles()");
    OpenFile(toFile, QIODevice::ReadWrite, "DataHandler::mergeTextFiles()");

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

      std::sort(dataRowsContainer.begin(), dataRowsContainer.end(), [](DataRow *ptr1, DataRow *ptr2) -> bool { return *ptr1 < *ptr2; });

      while (true) {
        DataRow* dataRow = new DataRow();
        dataRow->readTextDataFrom(from, mode);

        if (from.atEnd()) break;
      }

      writeDataToTextStream(to);
    }

    // TODO


  }
  catch(...) {
    if (fromFile.isOpen())  CloseFile(fromFile,  "DataHandler::mergeTextFiles()");
    if (toFile.isOpen()) CloseFile(toFile, "DataHandler::mergeTextFiles()");
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
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::decryptFile()");
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
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::decryptFile()");
    RemoveFile(tmpFile, "DataHandler::decryptFile()");
    throw;
  }
  CloseFile(tmpFile,  "DataHandler::decryptFile()");
  RemoveFile(tmpFile, "DataHandler::decryptFile()");
}


// uncompress data from input file to tmp data file
void DataHandler::uncompress(QDataStream& from, QDataStream& to) {
  unsigned long compressedDataSize   = 0;
  unsigned long uncompressedDataSize = 0;
  size_t ulSize      = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long
  size_t dataLength  = 0;

  dataLength         = from.device()->size();
  compressedDataSize = dataLength - ulSize; // 1st 4 bytes holds information about uncompressed data size

  ReadDataFromStream(from, uncompressedDataSize, ulSize, "DataHandler::uncompressFile()");

  uint8_t *inBuff  = nullptr;
  uint8_t *outBuff = nullptr;
  try {
    inBuff = new uint8_t[compressedDataSize];
    outBuff = new uint8_t[uncompressedDataSize];
    ReadDataFromStream(from, *inBuff, compressedDataSize, "DataHandler::uncompressFile()");
  }
  catch (...) {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::uncompressFile()\" allocated memory was failed.");
    throw;
  }

  int result = zlib::uncompress(outBuff, &uncompressedDataSize, inBuff, compressedDataSize);

  if (inBuff) delete[] inBuff;
  if (result == Z_OK) {
    WriteDataToStream(to, *outBuff, uncompressedDataSize, "DataHandler::uncompressFile()");
    if (outBuff) delete[] outBuff;
  } else {
    if (outBuff) delete[] outBuff;
    AddException("In function \"uncompressFile()\" uncompress was failed.");
    throw;
  }
}

// ============================================================================

// encrypt data to output binary file from data container
void DataHandler::encrypt(QVector<DataRow*>& from, QDataStream& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::encryptFile()");
    QDataStream tmp(&tmpFile);

    // write data rows to uncompressed tmp data file
    for (int i = 0; i < from.size(); i++) {
      from[i]->writeBinDataTo(tmp);
    }

    tmp.device()->seek(0); // set pos to file begin

    compress(tmp, to); // compress tmp data file to output file
  }
  catch (...) {
    if (tmpFile.isOpen()) CloseFile(tmpFile, "DataHandler::encryptFile()");
    RemoveFile(tmpFile, "DataHandler::encryptFile()");
    throw;
  }
  CloseFile(tmpFile,  "DataHandler::encryptFile()");
  RemoveFile(tmpFile, "DataHandler::encryptFile()");
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
    ReadDataFromStream(from, *inBuff, uncompressedDataSize, "DataHandler::compressFile()");
  }
  catch (...) {
    if (inBuff)  delete[] inBuff;
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::compressFile()\" allocated memory was failed.");
    throw;
  }

  int result = zlib::compress2(outBuff, &compressedDataSize, inBuff, uncompressedDataSize, Z_BEST_SPEED);

  if (inBuff)  delete[] inBuff;
  if (result == Z_OK) {
    WriteDataToStream(to, uncompressedDataSize, ulSize, "DataHandler::compressFile()");
    WriteDataToStream(to, *outBuff, compressedDataSize, "DataHandler::compressFile()");
    if (outBuff) delete[] outBuff;
  } else {
    if (outBuff) delete[] outBuff;
    AddException("In function \"DataHandler::compressFile()\" compress was failed.");
    throw;
  }
}
