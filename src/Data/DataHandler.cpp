#include <QString>
#include "DataHandler.hpp"
#include "DataRow.hpp"
#include "FileFunctions.hpp"


const uint32_t MAX_CODE    = 0x10ffff;
const uint16_t BOM_UTF16LE = 0xFEFF;

// =============================================================================

DataHandler::DataHandler() {}


DataHandler::~DataHandler() {
  resetData();
}

// PUBLIC METHODS ==============================================================

//
void DataHandler::mergeTwoFiles(const QString &filePath1, const QString &filePath2) {
  // TODO:
}


//
void DataHandler::convertBinFileToTextFile(const QString &binFilePath) {
  resetData(); // be on the safe side
  std::ifstream input;
  std::wofstream output;
  std::string path;
  try {
    path = binFilePath.toStdString();
    openInputFile(input, path, "DataHandler::convertBinFileToTextFile()");
    readDataFromBinFile(input);
    closeFile(input, path, "DataHandler::convertBinFileToTextFile()");
    path += ".txt";
    openOutputFile(output, path, "DataHandler::convertBinFileToTextFile()");
    writeDataToTextFile(output);
    closeFile(output, path, "DataHandler::convertBinFileToTextFile()");
  }
  catch (const std::exception &e) {
    if (input.is_open()) closeFile(input, path, "DataHandler::convertBinFileToTextFile()");
    if (output.is_open()) closeFile(output, path, "DataHandler::convertBinFileToTextFile()");
    throw;
  }
  resetData();
}


//
void DataHandler::convertTextFileToBinFile(const QString &textFilePath) {
  resetData(); // be on the safe side
  std::wifstream input;
  std::fstream output;
  std::string path;
  try {
    path = textFilePath.toStdString();
    openInputFile(input, path, "DataHandler::convertTextFileToBinFile()");
    readDataFromTextFile(input);
    closeFile(input, path, "DataHandler::convertTextFileToBinFile()");
    path += ".bin";
    openOutputFile(output, path, "DataHandler::convertTextFileToBinFile()");
    writeDataToBinFile(output);
    closeFile(output, path, "DataHandler::convertTextFileToBinFile()");
  }
  catch (const std::exception &e) {
    if (input.is_open()) closeFile(input, path, "DataHandler::convertTextFileToBinFile()");
    if (output.is_open()) closeFile(output, path, "DataHandler::convertTextFileToBinFile()");
    throw;
  }
  resetData();
}

// PRIVATE METHODS ==============================================================

// delete existed data
void DataHandler::resetData() {
  for (size_t i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
  dataRowsContainer.clear();
}


// read data rows from compressed input binary file
void DataHandler::readDataFromBinFile(std::ifstream& input) {
  try {
    decryptFile(input, dataRowsContainer);
  }
  catch (const std::exception& e) {
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


// write data rows to output text file (BOM_UTF16LE)
void DataHandler::readDataFromTextFile(std::wifstream& input) {
  try {
    input.imbue(std::locale(input.getloc(), new std::codecvt_utf16<wchar_t, MAX_CODE, std::little_endian>));
    uint16_t bom;
    input.read(reinterpret_cast<wchar_t*>(&bom), 1);
    while (true) {
      DataRow* dataRow = new DataRow();
      input >> *dataRow;
      if (input.eof()) break;
      dataRowsContainer.push_back(dataRow);
    }
  }
  catch (const std::exception &e) {
    throw;
  }
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
