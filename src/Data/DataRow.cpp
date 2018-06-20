#include "DataRow.hpp"
#include "FileFunctions.hpp"


DataRow::DataRow() {}

DataRow::~DataRow() {}

// =============================================================================


void ReplaceInString(std::wstring &string, const std::wstring &search, const std::wstring &replace) {
  std::wstring result;
  size_t prevPos = 0;
  size_t pos = 0;
  while (pos != std::wstring::npos) {
    pos = string.find(search, pos);
    result.append(string, prevPos, pos - prevPos);
    if (pos != std::wstring::npos) {
      result.append(replace);
      pos += search.size();
    }
    prevPos = pos;
  }
  string = result;
}


// std::getline() have bad work with some quotes symbols - they must be replaced
bool IsQuote(wchar_t wch) {
  for (size_t i = 0; i < (sizeof(quotesCodes) / sizeof(quotesCodes[0])); i++) {
    if (wch == quotesCodes[i]) return true;
  }
  return false;
}

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


// read from input stream
std::fstream& operator >> (std::fstream& input, DataRow& row) {
  readDataFromFile(input, row.size);
  readDataFromFile(input, row.type);
  readDataFromFile(input, row.id1);
  readDataFromFile(input, row.id2);
  readDataFromFile(input, row.id3.split[0]); // uint16_t low byte
  readDataFromFile(input, row.id4.split[0]);
  uint16_t wch;
  for (size_t i = 0; i < row.size; i++) {
    readDataFromFile(input, wch);
    if (wch == CR_CODE) continue;  // skip CR
    if  (wch == LF_CODE) {
      row.string.push_back(L'\\'); // replace LF to '\n'
      row.string.push_back(L'n');
    } else if (IsQuote(wch)) {
      row.string.push_back(L'"'); // replace all quotes to '"'
    } else {
      row.string.push_back(static_cast<wchar_t>(wch));
    }
  }
  readDataFromFile(input, wch); // read two null bytes
  readDataFromFile(input, wch);

  return input;
}


// write to out stream (binary mode)
std::fstream& operator << (std::fstream& output, DataRow& row) {
  writeDataToFile(output, row.size);
  writeDataToFile(output, row.type);
  writeDataToFile(output, row.id1);
  writeDataToFile(output, row.id2);
  writeDataToFile(output, row.id3.split[0]);
  writeDataToFile(output, row.id4.split[0]);
  for (size_t i = 1; i < row.string.size()-1; i++) { // skip first & last quotes
    uint16_t wch = row.string[i];
    writeDataToFile(output, wch);
  }
  uint16_t null = 0;
  writeDataToFile(output, null); // write two null bytes
  writeDataToFile(output, null);

  return output;
}


// read from in stream (text mode)
std::wifstream& operator >> (std::wifstream& input, DataRow& row) {
  input >> row.type;
  input >> row.id1;
  input >> row.id2;
  input >> row.id3.solid;
  input >> row.id4.solid;

  std::getline(input >> std::ws, row.string);

  ReplaceInString(row.string, L"\\n", L"\n"); // replace '\n' to LF
  row.size = row.string.size() - 2; // skip quotes

  return input;
}


// write to out stream (text mode)
std::wofstream& operator << (std::wofstream& output, DataRow& row) {
  output << std::dec << row.type << L'\t';
  output << std::dec << row.id1 << L'\t';
  output << std::dec << row.id2 << L'\t';
  output << std::dec << row.id3.solid << L'\t';
  output << std::dec << row.id4.solid << L'\t';
  output << L"\"" << row.string << L"\"" << std::endl;

  return output;
}
