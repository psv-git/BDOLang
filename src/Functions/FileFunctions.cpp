// https://www.zlib.net/manual.html
// http://zlib.net.ru/
// https://eax.me/zlib/

#include "FileFunctions.hpp"
#include "DataRow.hpp"


void removeFile(const std::string& fileName, const std::string& functionName) {
  int error = std::remove(fileName.c_str());
  if (error) {
    throw MyException("In function \"" + functionName + "\" removing \"" + fileName + "\" file was failed.");
  }
}

// =============================================================================

// decrypt data from input file to data container
void decryptFile(std::ifstream& from, std::vector<DataRow*>& to) {
  std::fstream tmp;
  openOutputFile(tmp, TMP_FILE_NAME, "decryptFile()");
  try {
    uncompressFile(from, tmp);
    closeFile(tmp, TMP_FILE_NAME, "decryptFile()");
    openInputFile(tmp, TMP_FILE_NAME, "decryptFile()");
    // decrypting uncompressed data
    while (true) {
      DataRow* dataRow = new DataRow();
      tmp >> *dataRow;
      if (tmp.eof()) break;
      to.push_back(dataRow);
    }
  }
  catch (const std::exception& e) {
    std::cerr << "test catch" << std::endl;
    if (tmp.is_open()) closeFile(tmp, TMP_FILE_NAME, "decryptFile()");
    removeFile(TMP_FILE_NAME, "decryptFile()");
    throw;
  }
  closeFile(tmp, TMP_FILE_NAME, "decryptFile()");
  removeFile(TMP_FILE_NAME, "decryptFile()");
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
    throw MyException("In function \"uncompressFile()\" getting compressed data size was failed.");
  }

  if (dataLength < MIN_DATA_LENGTH) {
    throw MyException("In function \"uncompressFile()\" bad data length.");
  }

  readDataFromFile(from, uncompressedDataSize, ulSize, "uncompressFile()");

  uint8_t *inBuff = nullptr, *outBuff = nullptr;
  try {
    inBuff = new uint8_t[compressedDataSize];
    outBuff = new uint8_t[uncompressedDataSize];
  }
  catch (...) {
    if (inBuff) delete[] inBuff;
    throw MyException("In function \"uncompressFile()\" allocated memory was failed.");
  }

  readDataFromFile(from, *inBuff, compressedDataSize, "uncompressFile()");

  int result = uncompress(outBuff, &uncompressedDataSize, inBuff, compressedDataSize);

  if (result == Z_OK) {
    writeDataToFile(to, *outBuff, uncompressedDataSize, "uncompressFile()");
  } else {
    throw MyException("In function \"uncompressFile()\" uncompress was failed.");
  }
}


// =============================================================================

// encrypt data to output binary file from data container
void encryptFile(std::vector<DataRow*>& from, std::fstream& to) {
  std::fstream tmp;
  openOutputFile(tmp, TMP_FILE_NAME, "encryptFile()");
  try {
    // write data rows to uncompressed tmp data file
    for (size_t i = 0; i < from.size(); i++) {
      tmp << *from[i];
    }

    closeFile(tmp, TMP_FILE_NAME, "encryptFile()");
    openInputFile(tmp, TMP_FILE_NAME, "encryptFile()");

    compressFile(tmp, to); // compress tmp data file to output file
  }
  catch (const std::exception& e) {
    if (tmp.is_open()) closeFile(tmp, TMP_FILE_NAME, "encryptFile()");
    removeFile(TMP_FILE_NAME, "encryptFile()");
    throw;
  }
  closeFile(tmp, TMP_FILE_NAME, "encryptFile()");
  removeFile(TMP_FILE_NAME, "encryptFile()");
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
    throw MyException("In function \"compressFile()\" getting uncompressed data size was failed.");
  }

  compressedDataSize = compressBound(uncompressedDataSize);

  uint8_t *inBuff = nullptr, *outBuff = nullptr;
  try {
    inBuff = new uint8_t[uncompressedDataSize];
    outBuff = new uint8_t[compressedDataSize];
  }
  catch (...) {
    if (inBuff) delete[] inBuff;
    throw MyException("In function \"compressFile()\" allocated memory was failed.");
  }

  readDataFromFile(from, *inBuff, uncompressedDataSize, "compressFile()");

  int result = compress2(outBuff, &compressedDataSize, inBuff, uncompressedDataSize, Z_BEST_SPEED);

  if (result == Z_OK) {
    writeDataToFile(to, uncompressedDataSize, ulSize, "compressFile()");
    writeDataToFile(to, *outBuff, compressedDataSize, "compressFile()");
  } else {
    throw MyException("In function \"compressFile()\" compress was failed.");
  }
}
