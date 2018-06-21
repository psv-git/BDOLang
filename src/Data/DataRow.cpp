#include "DataRow.hpp"


DataRow::DataRow() {}

DataRow::~DataRow() {}

// ============================================================================

void ReplaceInString(QString &string, const QString &search, const QString &replace) {
  QRegExp re(search);
  string.replace(search, replace);
}


//bool IsStringUTF16Cyrillic(const std::u16string &string) {
//  for (size_t i = 0; i <= string.size(); i++) {
//    if (string[i] >= RU_BEG && string[i] <= RU_END) return true;
//  }
//  return false;
//}

// PUBLIC METHODS =============================================================

// read from input stream
void DataRow::readBinDataFrom(QDataStream& input) {
  ReadDataFromStream(input, size, 0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, type, 0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id1,  0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id2,  0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id3,  1, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id4,  1, "DataRow::writeBinDataToRow()");
  char16_t wch;
  for (size_t i = 0; i < size; i++) {
    ReadDataFromStream(input, wch, 0, "DataRow::writeBinDataToRow()");
    if (wch == CR_CODE) continue;  // skip CR
    if (wch == LF_CODE) string.push_back("\\n"); // replace LF to '\n'
    else string.push_back(wch);
  }
  ReadDataFromStream(input, wch, 0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, wch, 0, "DataRow::writeBinDataToRow()");
}


// write to out stream (binary mode)
void DataRow::writeBinDataTo(QDataStream& output) {
  WriteDataToStream(output, size, 0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, type, 0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id1,  0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id2,  0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id3,  1, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id4,  1, "DataRow::readBinDataFromRow()");
  char16_t wch;
  for (int i = 1; i < string.size() - 1; i++) { // skip first & last quotes
    wch = string[i].unicode();
    WriteDataToStream(output, wch, 0, "DataRow::readBinDataFromRow()");
  }
  wch = 0x0000;
  WriteDataToStream(output, wch, 0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, wch, 0, "DataRow::readBinDataFromRow()");
}


// read from in stream (text mode)
void DataRow::readTextDataFrom(QTextStream& input) {
  input >> type;
  input >> id1;
  input >> id2;
  input >> id3;
  input >> id4;
  input >> string;

  ReplaceInString(string, "\\n", "\n"); // replace '\n' to LF
  size = string.size() - 2; // skip quotes
}


// write to out stream (text mode)
void DataRow::writeTextDataTo(QTextStream& output) {
  output << type << '\t';
  output << id1  << '\t';
  output << id2  << '\t';
  output << id3  << '\t';
  output << id4  << '\t';
  output << '\"' << string << '\"' << '\n';
}
