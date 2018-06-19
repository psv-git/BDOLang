#include "DataRow.hpp"
#include "FileFunctions.hpp"
#include "MyException.hpp"


const uint16_t CHAR_CR = 0x000D;
const uint16_t CHAR_LF = 0x000A;
const wchar_t CHAR_TAB = 0x0009;

// =============================================================================

DataRow::DataRow() {}

DataRow::~DataRow() {}

// PUBLIC METHODS ==============================================================

// compare two data rows
bool DataRow::operator < (const DataRow& row) const {
  if (type == row.type) {
    if (id1 == row.id1) {
      if (id2 == row.id2) {
        if (id3 == row.id3) return (id4 < row.id4);
        return (id3 < row.id3);
      }
      return (id2 < row.id2);
    }
    return (id1 < row.id1);
  }
  return (type < row.type);
}


// read from input stream
std::fstream& operator >> (std::fstream& input, DataRow& row) {
  // read header
  readDataFromFile(input, row.size);
  readDataFromFile(input, row.type);
  readDataFromFile(input, row.id1);
  readDataFromFile(input, row.id2);
  readDataFromFile(input, row.id3);
  readDataFromFile(input, row.id4);
  // read string
  row.string.clear();
  uint16_t wch;
  for (size_t i = 0; i < row.size; i++) {
    readDataFromFile(input, wch);
    row.string.push_back(static_cast<wchar_t>(wch));
  }
  // read two null bytes
  readDataFromFile(input, wch);
  readDataFromFile(input, wch);

  return input;
}


// write to out stream (text mode)
std::wofstream& operator << (std::wofstream& output, DataRow& row) {
  output << std::dec << row.type << L'\t';
  output << std::dec << row.id1 << L'\t';
  output << std::dec << row.id2 << L'\t';
  output << std::dec << row.id3 << L'\t';
  output << std::dec << row.id4 << L'\t';
  output << L"\"" << row.string << "\"" << L'\n';

  return output;
}


// write to out stream (binary mode)
std::fstream& operator << (std::fstream& output, DataRow& row) {
  writeDataToFile(output, row.size);
  writeDataToFile(output, row.type);
  writeDataToFile(output, row.id1);
  writeDataToFile(output, row.id2);
  writeDataToFile(output, row.id3);
  writeDataToFile(output, row.id4);
  for (size_t i = 0; i < row.string.size(); i++) {
    uint16_t wch = row.string[i];
    writeDataToFile(output, wch);
  }
  uint16_t null = 0;
  writeDataToFile(output, null);
  writeDataToFile(output, null);

  return output;
}
