#include "DataRow.hpp"


DataRow::DataRow() {}

DataRow::~DataRow() {}

// ============================================================================

//bool IsStringUTF16Cyrillic(const std::u16string &string) {
//  for (size_t i = 0; i <= string.size(); i++) {
//    if (string[i] >= RU_BEG && string[i] <= RU_END) return true;
//  }
//  return false;
//}

// PUBLIC METHODS =============================================================

// read from input stream (binary mode)
void DataRow::readBinDataFrom(QDataStream& input) {
  ReadDataFromStream(input, size, 0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, type, 0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id1,  0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id2,  0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id3.split[0],  0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id4.split[0],  0, "DataRow::writeBinDataToRow()");
  char16_t wch;
  for (size_t i = 0; i < size; i++) {
    ReadDataFromStream(input, wch, 0, "DataRow::writeBinDataToRow()");
    if (wch == CR_CODE) continue;                // skip CR
    if (wch == LF_CODE) string.push_back("\\n"); // replace LF to '\n'
    else string.push_back(wch);
  }
  // read four null bytes
  ReadDataFromStream(input, wch, 0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, wch, 0, "DataRow::writeBinDataToRow()");
}


// write to out stream (binary mode)
void DataRow::writeBinDataTo(QDataStream& output) {
  WriteDataToStream(output, size, 0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, type, 0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id1,  0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id2,  0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id3.split[0],  0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id4.split[0],  0, "DataRow::readBinDataFromRow()");
  char16_t wch;
  for (int i = 0; i < string.size(); i++) {
    wch = static_cast<char16_t>(string[i].unicode());
    WriteDataToStream(output, wch, 0, "DataRow::readBinDataFromRow()");
  }
  // write four null bytes
  wch = 0x0000;
  WriteDataToStream(output, wch, 0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, wch, 0, "DataRow::readBinDataFromRow()");
}


// read from in stream (text mode)
void DataRow::readTextDataFrom(QTextStream& input) {
  input >> type;
  input >> id1;
  input >> id2;
  input >> id3.solid;
  input >> id4.solid;
  input.readLineInto(&string);

  // formating string
  QRegularExpression rempat("(^\t\"|\r|\"$)");
  QRegularExpression reppat("\\\\n");
  string.remove(rempat);        // remove tabulation, quotes, CR
  string.replace(reppat, "\n"); // replace '\n' to LF

  size = static_cast<unsigned long>(string.count());
}


// write to out stream (text mode)
void DataRow::writeTextDataTo(QTextStream& output) {
  output << type       << '\t';
  output << id1        << '\t';
  output << id2        << '\t';
  output << id3.solid  << '\t';
  output << id4.solid  << '\t';
  output << '"' << string << '"' << '\n';
}
