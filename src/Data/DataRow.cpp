#include "DataRow.hpp"
#include "FileFunctions.hpp"


DataRow::DataRow() {}

DataRow::~DataRow() {}

// =============================================================================

void ReplaceInString(std::u16string &string, const std::u16string &search, const std::u16string &replace) {
  std::u16string result;
  size_t prevPos = 0;
  size_t pos = 0;
  while (pos != std::u16string::npos) {
    pos = string.find(search, pos);
    result.append(string, prevPos, pos - prevPos);
    if (pos != std::u16string::npos) {
      result.append(replace);
      pos += search.size();
    }
    prevPos = pos;
  }
  string = result;
}


// std::getline() have bad work with some quotes symbols - they must be replaced
bool IsQuote(char16_t ch) {
  for (size_t i = 0; i < (sizeof(quotesCodes) / sizeof(quotesCodes[0])); i++) {
    if (ch == quotesCodes[i]) return true;
  }
  return false;
}


bool IsStringUTF16Cyrillic(const std::u16string &string) {
  for (size_t i = 0; i <= string.size(); i++) {
    if (string[i] >= RU_BEG && string[i] <= RU_END) return true;
  }
  return false;
}

//template <typename T>
//std::u16string to_u16string(const T &t) {
//  std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::little_endian>, char16_t> conv;
//  return conv.from_bytes(std::to_string(t));
//}

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
  char16_t ch;
  for (size_t i = 0; i < row.size; i++) {
    readDataFromFile(input, ch);
    if (ch == CR_CODE) continue;  // skip CR
    if  (ch == LF_CODE) {
      row.string.push_back(u'\\'); // replace LF to '\n'
      row.string.push_back(u'n');
    } else if (IsQuote(ch)) {
      row.string.push_back(u'"'); // replace all quotes to '"'
    } else {
      row.string.push_back(ch);
    }
  }
  readDataFromFile(input, ch); // read two null bytes
  readDataFromFile(input, ch);

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
  for (size_t i = 1; i < row.string.size() - 1; i++) { // skip first & last quotes
    char16_t ch = row.string[i];
    writeDataToFile(output, ch);
  }
  uint16_t null = 0;
  writeDataToFile(output, null); // write four null bytes
  writeDataToFile(output, null);

  return output;
}


// read from in stream (text mode)
u16ifstream& operator >> (u16ifstream& input, DataRow& row) {
  input >> row.type;
  input >> row.id1;
  input >> row.id2;
  input >> row.id3.solid;
  input >> row.id4.solid;

//  std::string wstr;
//  std::getline(input >> std::ws, wstr);

//  std::wstring_convert<std::codecvt_utf16<wchar_t>> cv;
//  row.string = cv.to_bytes(wstr);


  ReplaceInString(row.string, u"\\n", u"\n"); // replace '\n' to LF
  row.size = row.string.size() - 2; // skip quotes

  return input;
}


// write to out stream (text mode)
u16ofstream& operator << (u16ofstream& output, DataRow& row) {
  output << to_u16string(row.type) << u'\t';
  output << to_u16string(row.id1) << u'\t';
  output << to_u16string(row.id2) << u'\t';
  output << to_u16string(row.id3.solid) << u'\t';
  output << to_u16string(row.id4.solid) << u'\t';
  output << u'\"' << row.string << u'\"' << u'\n';

  return output;
}
