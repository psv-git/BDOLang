#include "DataHandler.hpp"
#include "../Functions/FileFunctions.hpp"
#include "DataRow.hpp"


DataHandler::DataHandler() : usedMemory(0) {}

DataHandler::~DataHandler() {
  // delete data rows
  for (size_t i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
}

// PUBLIC METHODS ==============================================================

// read data rows from compressed input binary file
void DataHandler::readDataFromBinFile(std::ifstream& input) {
  try {
    decryptFile(input, dataRowsContainer);
  }
  catch (const std::exception& e) {
    throw;
  }
  // get used memory size
  for (size_t i = 0; i < dataRowsContainer.size(); i++) {
    usedMemory += dataRowsContainer[i]->getMemorySize();
  }
  usedMemory /= MB_SIZE;
}


// write data rows to output text file (BOM_UTF16LE)
void DataHandler::writeDataToTextFile(std::wofstream& output) {
  try {
    output.imbue(std::locale(output.getloc(), new std::codecvt_utf16<wchar_t, MAX_CODE, std::little_endian>));
    output.put(BOM_UTF16LE);
    for (size_t i = 0; i < dataRowsContainer.size(); i++) {
      output << *dataRowsContainer[i];
    }
  }
  catch (const std::exception &e) {
    throw;
  }
}


// write data rows to compressed output bin file
void DataHandler::writeDataToBinFile(std::fstream& output) {
  try {
    encryptFile(dataRowsContainer, output);
  }
  catch (const std::exception& e) {
    throw;
  }
}


// get used memory
size_t DataHandler::getUsedMemory() const {
  return usedMemory;
}

// PRIVATE METHODS =============================================================

// void DataHandler::sortData() {}
