#include "DataRow.hpp"
#include "FileFunctions.hpp"
#include "MyException.hpp"


const uint16_t CR_CODE = 0x000D;
const uint16_t LF_CODE = 0x000A;
const wchar_t CR = 0x000D;
const wchar_t LF = 0x000A;

// =============================================================================

DataRow::DataRow() {}

DataRow::~DataRow() {}

// PUBLIC METHODS ==============================================================

// compare two data rows
//bool DataRow::operator < (const DataRow& row) const {
//  if (type == row.type) {
//    if (id1 == row.id1) {
//      if (id2 == row.id2) {
//        if (id3 == row.id3) return (id4 < row.id4);
//        return (id3 < row.id3);
//      }
//      return (id2 < row.id2);
//    }
//    return (id1 < row.id1);
//  }
//  return (type < row.type);
//}


// FUCKING QUOTES!!!11111
uint16_t quotesCodes[] = { 0x201C, 0x201D, 0x201E, 0x201F };
bool isQuote(uint16_t wch) {
  for (int i = 0; i < (sizeof(quotesCodes) / sizeof(uint16_t)); i++) {
    if (wch == quotesCodes[i]) return true;
  }
  return false;
}

// read from input stream
std::fstream& operator >> (std::fstream& input, DataRow& row) {
  // read header
  readDataFromFile(input, row.size);
  readDataFromFile(input, row.type);
  readDataFromFile(input, row.id1);
  readDataFromFile(input, row.id2);
  readDataFromFile(input, row.id3, 1); // meaning uint8_t
  readDataFromFile(input, row.id4, 1); // meaning uint8_t
  // read string
  row.string.clear();
  uint16_t wch;
  for (size_t i = 0; i < row.size; i++) {
    readDataFromFile(input, wch);
    if (wch == CR_CODE) {
      continue;
    } else if  (wch == LF_CODE) {
      row.string.push_back(L'\\');
      row.string.push_back(L'n');
    } else if (isQuote(wch)) {
      row.string.push_back(L'"');
    } else {
      row.string.push_back(static_cast<wchar_t>(wch));
    }
  }
  // read two null bytes
  readDataFromFile(input, wch);
  readDataFromFile(input, wch);

  return input;
}


// write to out stream (binary mode)
std::fstream& operator << (std::fstream& output, DataRow& row) {
  writeDataToFile(output, row.size);
  writeDataToFile(output, row.type);
  writeDataToFile(output, row.id1);
  writeDataToFile(output, row.id2);
  writeDataToFile(output, row.id3, 1);
  writeDataToFile(output, row.id4, 1);
  for (size_t i = 0; i < row.string.size(); i++) {
    uint16_t wch = row.string[i];
    writeDataToFile(output, wch);
  }
  uint16_t null = 0;
  writeDataToFile(output, null);
  writeDataToFile(output, null);

  return output;
}


// replace '\n' to LF in string
void ReplaceN(std::wstring &str) {
  std::vector<size_t> findedPos;
  size_t currPos = 0, findPos = 0;
  while (true) {
    findPos = str.find(L"\n", currPos);
    currPos = findPos;
    if (findPos != std::string::npos) {
      findedPos.push_back(findPos);
      currPos = findPos;
    } else break;
  }
  for (size_t i = 0; i < findedPos.size(); i++) {
    str.replace(findedPos[i], 2, 1, LF);
  }
}

// read from in stream (text mode)
std::wifstream& operator >> (std::wifstream& input, DataRow& row) {
  input >> row.type >> row.id1 >> row.id2 >> row.id3 >> row.id4;
  getline(input >> std::ws, row.string);
  ReplaceN(row.string);

  return input;
}


// write to out stream (text mode)
std::wofstream& operator << (std::wofstream& output, DataRow& row) {
  output << std::dec << row.type << L'\t';
  output << std::dec << row.id1 << L'\t';
  output << std::dec << row.id2 << L'\t';
  output << std::dec << row.id3 << L'\t';
  output << std::dec << row.id4 << L'\t';
  output << row.string << std::endl;

  return output;
}
