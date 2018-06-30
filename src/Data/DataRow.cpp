#include "DataRow.hpp"


const char16_t CR_CODE = 0x000D;
const char16_t LF_CODE = 0x000A;

// ============================================================================

DataRow::DataRow() {}

DataRow::~DataRow() {}

// ============================================================================

bool operator < (const DataRow& row1, const DataRow& row2) {
  if (row1.sheet < row2.sheet)         return true;
  if (row1.sheet > row2.sheet)         return false;
  if (row1.id1 < row2.id1)             return true;
  if (row1.id1 > row2.id1)             return false;
  if (row1.id2 < row2.id2)             return true;
  if (row1.id2 > row2.id2)             return false;
  if (row1.id3.solid < row2.id3.solid) return true;
  if (row1.id3.solid > row2.id3.solid) return false;
  if (row1.id4.solid < row2.id4.solid) return true;
  return false;
}


bool operator == (const DataRow& row1, const DataRow& row2) {
  if (row1.sheet != row2.sheet)         return false;
  if (row1.id1 != row2.id1)             return false;
  if (row1.id2 != row2.id2)             return false;
  if (row1.id3.solid != row2.id3.solid) return false;
  if (row1.id4.solid != row2.id4.solid) return false;
  return true;
}

// getters/setters ============================================================

unsigned long  DataRow::getSheet() const { return sheet; }
const QString DataRow::getString() const { return string; }

void DataRow::setString(const QString &string) { DataRow::string = string; }

// public methods =============================================================

// read from input stream (binary mode)
void DataRow::readBinDataFrom(QDataStream& input) {
  try {
    ReadDataFromStream(input, size,  0);
    ReadDataFromStream(input, sheet, 0);
    ReadDataFromStream(input, id1,   0);
    ReadDataFromStream(input, id2,   0);
    ReadDataFromStream(input, id3.split[0],  0);
    ReadDataFromStream(input, id4.split[0],  0);
    char16_t wch;
    for (size_t i = 0; i < static_cast<int>(size); i++) {
      ReadDataFromStream(input, wch, 0);
      if (wch == CR_CODE) continue;                // skip CR if exist
      if (wch == LF_CODE) string.push_back("\\n"); // replace LF to '\n'
      else string.push_back(wch);
    }
    // read four null bytes
    ReadDataFromStream(input, wch, 0);
    ReadDataFromStream(input, wch, 0);
  }
  catch (const std::ios_base::failure &err) { throw err; }
}


// write to out stream (binary mode)
void DataRow::writeBinDataTo(QDataStream& output) {
  QRegularExpression reppat("\\\\n");
  string.replace(reppat, "\n"); // replace '\n' to LF
  try {
    size = static_cast<unsigned long>(string.count());
    WriteDataToStream(output, size,  0);
    WriteDataToStream(output, sheet, 0);
    WriteDataToStream(output, id1,   0);
    WriteDataToStream(output, id2,   0);
    WriteDataToStream(output, id3.split[0],  0);
    WriteDataToStream(output, id4.split[0],  0);
    char16_t wch;
    for (int i = 0; i < static_cast<int>(size); i++) {
      wch = static_cast<char16_t>(string[i].unicode());
      WriteDataToStream(output, wch, 0);
    }
    // write four null bytes
    wch = 0x0000;
    WriteDataToStream(output, wch, 0);
    WriteDataToStream(output, wch, 0);
  }
  catch (const std::ios_base::failure &err) { throw err; }
}


// read from in stream (text mode)
void DataRow::readTextDataFrom(QTextStream& input) {
  input >> sheet;
  input >> id1;
  input >> id2;
  input >> id3.solid;
  input >> id4.solid;
  input.readLineInto(&string);

  if (input.status() == QTextStream::ReadCorruptData) throw std::ios_base::failure("read data from file was failed.");

  // formating string
  QRegularExpression rempat("(^\t\"|\r|\"$)");
  string.remove(rempat); // remove tabulation, quotes, CR
}


// write to out stream (text mode)
void DataRow::writeTextDataTo(QTextStream& output) {
  output << sheet     << '\t';
  output << id1       << '\t';
  output << id2       << '\t';
  output << id3.solid << '\t';
  output << id4.solid << '\t';
  output << '"' << string << '"' << '\n';

  if (output.status() == QTextStream::WriteFailed) throw std::ios_base::failure("write data from file was failed.");
}
