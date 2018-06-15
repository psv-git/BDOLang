// https://www.zlib.net/manual.html
// http://zlib.net.ru/
// https://eax.me/zlib/

#include "FileFunctions.hpp"
#include "../Data/DataRow.hpp"


void removeFile(const std::string& fileName) {
  int error = std::remove(fileName.c_str());
  if (error) {
    throw MyException("removing \"" + fileName + "\" file was failed.", 14);
  }
}

// =============================================================================

// decrypt data from input file to data container
void decryptFile(std::ifstream& from, std::vector<DataRow*>& to) {
  std::fstream tmp;
  openOutputFile(tmp, TMP_FILE_NAME);
  try {
    uncompressFile(from, tmp);
    closeFile(tmp, TMP_FILE_NAME);
    openInputFile(tmp, TMP_FILE_NAME);
    // decrypting uncompressed data
    while (true) {
      DataRow* dataRow = new DataRow();
      tmp >> *dataRow;
      if (tmp.eof()) break;
      to.push_back(dataRow);
    }
  }
  catch (const std::exception& e) {
    if (tmp.is_open()) closeFile(tmp, TMP_FILE_NAME);
    removeFile(TMP_FILE_NAME);
    throw;
  }
  closeFile(tmp, TMP_FILE_NAME);
  removeFile(TMP_FILE_NAME);
}


// uncompress data from input file to tmp data file
void uncompressFile(std::ifstream& from, std::fstream& to) {
  unsigned long compressedDataSize = 0;
  unsigned long uncompressedDataSize = 0;
  size_t ulSize = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long
  size_t dataLength = 0;

  try {
    from.seekg(0, std::ios::end);
    dataLength = from.tellg();
    compressedDataSize = dataLength - ulSize; // 1st 4 bytes holds information about uncompressed data size
    from.seekg(0, std::ios::beg);
  }
  catch (...) {
    throw MyException("getting compressed data size was failed.", 21);
  }

  if (dataLength < MIN_DATA_LENGTH) {
    throw MyException("bad data length.", 22);
  }

  readDataFromFile(from, uncompressedDataSize, ulSize);

  uint8_t *inBuff = nullptr, *outBuff = nullptr;
  try {
    inBuff = new uint8_t[compressedDataSize];
    outBuff = new uint8_t[uncompressedDataSize];
  }
  catch (...) {
    if (inBuff) delete[] inBuff;
    throw MyException("allocated memory was failed.", 23);
  }

  readDataFromFile(from, *inBuff, compressedDataSize);

  int result = uncompress(outBuff, &uncompressedDataSize, inBuff, compressedDataSize);

  if (result == Z_OK) {
    writeDataToFile(to, *outBuff, uncompressedDataSize);
  } else {
    throw MyException("uncompress was failed.", 24);
  }
}


// =============================================================================

// encrypt data to output binary file from data container
void encryptFile(std::vector<DataRow*>& from, std::fstream& to) {
  std::fstream tmp;
  openOutputFile(tmp, TMP_FILE_NAME);
  try {
    // write data rows to uncompressed tmp data file
    for (size_t i = 0; i < from.size(); i++) {
      tmp << *from[i];
    }

    closeFile(tmp, TMP_FILE_NAME);
    openInputFile(tmp, TMP_FILE_NAME);

    compressFile(tmp, to); // compress tmp data file to output file
  }
  catch (const std::exception& e) {
    if (tmp.is_open()) closeFile(tmp, TMP_FILE_NAME);
    removeFile(TMP_FILE_NAME);
    throw;
  }
  closeFile(tmp, TMP_FILE_NAME);
  removeFile(TMP_FILE_NAME);
}


// 
void compressFile(std::fstream& from, std::fstream& to) {
  unsigned long uncompressedDataSize = 0;
  unsigned long compressedDataSize = 0;
  size_t ulSize = sizeof(uint32_t); // guaranteed 4 bytes length for unsigned long

  try {
    from.seekg(0, std::ios::end);
    uncompressedDataSize = from.tellg();
    from.seekg(0, std::ios::beg);
  }
  catch (...) {
    throw MyException("getting uncompressed data size was failed.", 31);
  }

  compressedDataSize = compressBound(uncompressedDataSize);

  uint8_t *inBuff = nullptr, *outBuff = nullptr;
  try {
    inBuff = new uint8_t[uncompressedDataSize];
    outBuff = new uint8_t[compressedDataSize];
  }
  catch (...) {
    if (inBuff) delete[] inBuff;
    throw MyException("allocated memory was failed.", 32);
  }

  readDataFromFile(from, *inBuff, uncompressedDataSize);

  int result = compress2(outBuff, &compressedDataSize, inBuff, uncompressedDataSize, Z_BEST_SPEED);

  if (result == Z_OK) {
    writeDataToFile(to, uncompressedDataSize, ulSize);
    writeDataToFile(to, *outBuff, compressedDataSize);
  } else {
    throw MyException("compress was failed.", 33);
  }
}
