#ifndef FILEFUNCTIONS_HPP
#define FILEFUNCTIONS_HPP

#include "../Global/Global.hpp"
#include "../Exceptions/MyException.hpp"

class DataRow;


template <typename F>
void openInputFile(F& input, const std::string& fileName) {
  input.open(fileName, std::ios::in | std::ios::binary);
  if (input.fail()) {
    throw MyException("opening \"" + fileName + "\" file was failed.", 11);
  }
}


template <typename F>
void openOutputFile(F& output, const std::string& fileName) {
  output.open(fileName, std::ios::out | std::ios::binary);
  if (output.fail()) {
    throw MyException("opening \"" + fileName + "\" file was failed.", 12);
  }
}


template <typename F>
void closeFile(F& file, const std::string& fileName) {
  file.close();
  if (file.fail()) {
    throw MyException("file \"" + fileName + " was not closed.", 13);
  }
}


void removeFile(const std::string& fileName);


template <typename F, typename V>
void readDataFromFile(F& file, V& var, size_t size = 0) {
  if (size == 0) size = sizeof(var);
  file.read(reinterpret_cast<char*>(&var), size);
  if (file.fail() && !file.eof()) {
    throw MyException("read data from file was failed.", 15);
  }
}


template <typename F, typename V>
void writeDataToFile(F& file, V& var, size_t size = 0) {
  if (size == 0) size = sizeof(var);
  file.write(reinterpret_cast<char*>(&var), size);
  if (file.fail()) {
    throw MyException("write data to file was failed.", 16);
  }
}

// =============================================================================

// decrypt data from input file to data container
void decryptFile(std::ifstream& from, std::vector<DataRow*>& to);

// uncompress data from input file to tmp data file
void uncompressFile(std::ifstream& from, std::fstream& to);

// encrypt data to output binary file from data container
void encryptFile(std::vector<DataRow*>& from, std::fstream& to);

// compress binary tmp data file to binary output file
void compressFile(std::fstream& from, std::fstream& to);

#endif // FILEFUNCTIONS_HPP