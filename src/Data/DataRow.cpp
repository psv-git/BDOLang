#include "DataRow.hpp"


const char16_t CR_CODE = 0x000D;
const char16_t LF_CODE = 0x000A;

// ============================================================================

DataRow::DataRow() {}

DataRow::~DataRow() {}

// ============================================================================

bool DataRow::operator < (const DataRow& row) const {
  if (sheet < row.getSheet())   return true;
  if (sheet > row.getSheet())   return false;
  if (id1 < row.getId1())       return true;
  if (id1 > row.getId1())       return false;
  if (id2 < row.getId2())       return true;
  if (id2 > row.getId2())       return false;
  if (id3.solid < row.getId3()) return true;
  if (id3.solid > row.getId3()) return false;
  if (id4.solid < row.getId4()) return true;
  return false;
}

// PUBLIC METHODS =============================================================

unsigned long  DataRow::getSheet() const { return sheet; }
unsigned long  DataRow::getId1()   const { return id1; }
unsigned short DataRow::getId2()   const { return id2; }
unsigned short DataRow::getId3()   const { return id3.solid; }
unsigned short DataRow::getId4()   const { return id4.solid; }


// read from input stream (binary mode)
void DataRow::readBinDataFrom(QDataStream& input) {
  ReadDataFromStream(input, size,  0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, sheet, 0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id1,   0, "DataRow::writeBinDataToRow()");
  ReadDataFromStream(input, id2,   0, "DataRow::writeBinDataToRow()");
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
  WriteDataToStream(output, size,  0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, sheet, 0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id1,   0, "DataRow::readBinDataFromRow()");
  WriteDataToStream(output, id2,   0, "DataRow::readBinDataFromRow()");
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
  input >> sheet;
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
  output << sheet     << '\t';
  output << id1       << '\t';
  output << id2       << '\t';
  output << id3.solid << '\t';
  output << id4.solid << '\t';
  output << '"' << string << '"' << '\n';
}
