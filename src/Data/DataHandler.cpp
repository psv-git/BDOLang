#include <QString>
#include "DataHandler.hpp"
#include "DataRow.hpp"
#include "FileFunctions.hpp"


const uint32_t MAX_CODE = 0x10ffff;
const uint16_t BOM_UTF16LE = 0xFEFF;

// =============================================================================

DataHandler::DataHandler() : dataExist(false) {}


DataHandler::~DataHandler() {
  resetData();
}

// PUBLIC METHODS ==============================================================

//
void DataHandler::mergeTwoFiles(const QString &fileName1, const QString &fileName2) {

}


//
void DataHandler::convertBinFileToTextFile(const QString &binFileName) {
  std::ifstream input;
  std::wofstream output;
  std::string path;
  try {
    path = binFileName.toStdString();
    if (!dataExist) {
      openInputFile(input, path, "DataHandler::convertBinFileToTextFile()");
      readDataFromBinFile(input);
      closeFile(input, path, "TranslateWindow::show()");
      dataExist = true;
    }
    path += ".txt";
    openOutputFile(output, path, "DataHandler::convertBinFileToTextFile()");
    writeDataToTextFile(output);
    closeFile(output, path, "TranslateWindow::show()");
  }
  catch (const std::exception &e) {
    if (input.is_open()) closeFile(input, path, "TranslateWindow::show()");
    if (output.is_open()) closeFile(output, path, "TranslateWindow::show()");
    throw;
  }
}


// reset existed data
void DataHandler::resetData() {
  for (size_t i = 0; i < dataRowsContainer.size(); i++) {
    delete dataRowsContainer[i];
  }
  dataRowsContainer.clear();
  dataExist = false;
}


//
bool DataHandler::isDataExist() {
  return dataExist;
}

// PRIVATE METHODS ==============================================================

// read data rows from compressed input binary file
void DataHandler::readDataFromBinFile(std::ifstream& input) {
  try {
    decryptFile(input, dataRowsContainer);
  }
  catch (const std::exception& e) {
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


// write data rows to compressed output bin file
void DataHandler::writeDataToBinFile(std::fstream& output) {
  try {
    encryptFile(dataRowsContainer, output);
  }
  catch (const std::exception& e) {
    throw;
  }
}
