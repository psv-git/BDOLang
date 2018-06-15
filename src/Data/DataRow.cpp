#include "DataRow.hpp"
#include "../Functions/FileFunctions.hpp"
#include "../Exceptions/MyException.hpp"


DataRow::DataRow() : language(LANG::EN) {}

DataRow::~DataRow() {}

// PUBLIC METHODS ==============================================================

// compare two data rows
bool DataRow::operator < (const DataRow& row) const {
	if (type == row.type) {
		if (id1 == row.id1) {
			if (id2 == row.id2) {
				if (id3 == row.id3) {
					return (id4 < row.id4);
				}
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
  output << std::dec << row.type << static_cast<wchar_t>(CHAR_TAB);
  output << std::dec << row.id1 << static_cast<wchar_t>(CHAR_TAB);
  output << std::dec << row.id2 << static_cast<wchar_t>(CHAR_TAB);
  output << std::dec << row.id3 << static_cast<wchar_t>(CHAR_TAB);
  output << std::dec << row.id4 << static_cast<wchar_t>(CHAR_TAB);
  output << L"\"" << row.string << "\"" << static_cast<wchar_t>(CHAR_CR) << static_cast<wchar_t>(CHAR_LF);

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


size_t DataRow::getMemorySize() {
  return sizeof(size) + sizeof(type) + sizeof(id1) + sizeof(id2) + sizeof(id3) + sizeof(id4) + (sizeof(wchar_t) * string.size());
}

// PRIVATE METHODS =============================================================
