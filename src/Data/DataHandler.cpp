#include "DataHandler.hpp"
#include "DataRow.hpp"
#include <zlib.h>


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

    if (mode == MODE::TEXT_TO_TEXT) {
      QTextStream from(&fromFile);
      from.setAutoDetectUnicode(true);
      from.skipWhiteSpace();
      QTextStream to(&toFile);
      to.setAutoDetectUnicode(true);
      to.skipWhiteSpace();
      output.setCodec("UTF-8");
      output.setGenerateByteOrderMark(true);

      readDataFromTextFile(to); // save data; now we may rewrite file
    }

    to.device()->seek(0);     // back to begin file

    // TODO


  }
  catch() {
    if (fromFile.isOpen())  CloseFile(fromFile,  "DataHandler::mergeTextFiles()");
    if (toFile.isOpen()) CloseFile(toFile, "DataHandler::mergeTextFiles()");
    throw;
  }
}


//
void DataHandler::convertBinFileToTextFile(const QString &binFilePath, const QString &textFilePath) {
  QFile inputFile(binFilePath);
  QFile outputFile(textFilePath);
  try {
    OpenFile(inputFile,  QIODevice::ReadOnly, "DataHandler::convertBinFileToTextFile()");
    OpenFile(outputFile, QIODevice::WriteOnly, "DataHandler::convertBinFileToTextFile()");
    QDataStream input(&inputFile);
    QTextStream output(&outputFile);
    output.setCodec("UTF-8");
    output.setGenerateByteOrderMark(true);

    readDataFromBinFile(input);
    writeDataToTextFile(output);

    CloseFile(inputFile,  "DataHandler::convertBinFileToTextFile()");
    CloseFile(outputFile, "DataHandler::convertBinFileToTextFile()");
  }
  catch (...) {
    if (inputFile.isOpen())  CloseFile(inputFile,  "DataHandler::convertBinFileToTextFile()");
    if (outputFile.isOpen()) CloseFile(outputFile, "DataHandler::convertBinFileToTextFile()");
    throw;
  }
}


//
void DataHandler::convertTextFileToBinFile(const QString &textFilePath, const QString &binFilePath) {
  QFile inputFile(textFilePath);
  QFile outputFile(binFilePath);
  try {
    OpenFile(inputFile,  QIODevice::ReadOnly, "DataHandler::convertTextFileToBinFile()");
    OpenFile(outputFile, QIODevice::WriteOnly, "DataHandler::convertTextFileToBinFile()");
    QTextStream input(&inputFile);
    QDataStream output(&outputFile);
    input.setAutoDetectUnicode(true);
    input.skipWhiteSpace();

    readDataFromTextFile(input);
    writeDataToBinFile(output);

    CloseFile(inputFile,  "DataHandler::convertTextFileToBinFile()");
    CloseFile(outputFile, "DataHandler::convertTextFileToBinFile()");
  }
  catch (...) {
    if (inputFile.isOpen())  CloseFile(inputFile,  "DataHandler::convertTextFileToBinFile()");
    if (outputFile.isOpen()) CloseFile(outputFile, "DataHandler::convertTextFileToBinFile()");
    throw;
  }
}

// PRIVATE METHODS ============================================================

// delete existed data
void DataHandler::resetData() {
  for (size_t i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
  dataRowsContainer.clear();
}


// read data rows from compressed input binary file
void DataHandler::readDataFromBinFile(QDataStream& input) {
  try {
    decryptFile(input, dataRowsContainer);
  }
  catch (...) { throw; }
}


// write data rows to compressed output bin file
void DataHandler::writeDataToBinFile(QDataStream& output) {
  try {
    encryptFile(dataRowsContainer, output);
  }
  catch (...) { throw; }
}


// read data rows from input text file
void DataHandler::readDataFromTextFile(QTextStream& input) {
  try {
    while (true) {
      DataRow* dataRow = new DataRow();
      dataRow->readTextDataFrom(input);
      dataRowsContainer.push_back(dataRow);
      if (input.atEnd()) break;
    }
  }
  catch (...) { throw; }
}


// write data rows to output text file
void DataHandler::writeDataToTextFile(QTextStream& output) {
  try {
    for (size_t i = 0; i < dataRowsContainer.size(); i++) {
      dataRowsContainer[i]->writeTextDataTo(output);
    }
  }
  catch (...) { throw; }
}

// ============================================================================

// decrypt data from input file to data container
void DataHandler::decryptFile(QDataStream& from, std::vector<DataRow*>& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::decryptFile()");
    QDataStream tmp(&tmpFile);

    uncompressFile(from, tmp);

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
void DataHandler::uncompressFile(QDataStream& from, QDataStream& to) {
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

  int result = uncompress(outBuff, &uncompressedDataSize, inBuff, compressedDataSize);

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
void DataHandler::encryptFile(std::vector<DataRow*>& from, QDataStream& to) {
  QFile tmpFile(TMP_FILE_NAME);
  try {
    OpenFile(tmpFile, QIODevice::ReadWrite, "DataHandler::encryptFile()");
    QDataStream tmp(&tmpFile);

    // write data rows to uncompressed tmp data file
    for (size_t i = 0; i < from.size(); i++) {
      from[i]->writeBinDataTo(tmp);
    }

    tmp.device()->seek(0); // set pos to file begin

    compressFile(tmp, to); // compress tmp data file to output file
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
void DataHandler::compressFile(QDataStream& from, QDataStream& to) {
  unsigned long uncompressedDataSize = 0;
  unsigned long compressedDataSize   = 0;
  size_t ulSize = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long

  uncompressedDataSize = from.device()->size();
  compressedDataSize   = compressBound(uncompressedDataSize);

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

  int result = compress2(outBuff, &compressedDataSize, inBuff, uncompressedDataSize, Z_BEST_SPEED);

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
