// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#include "DataRow.hpp"


// UTF-16BE symbol codes
const char16_t CR_CODE = 0x000D;
const char16_t LF_CODE = 0x000A;
const char16_t CYR_BEG_CODE = 0x0400;
const char16_t CYR_END_CODE = 0x04FF;

// ============================================================================

DataRow::DataRow() {}

DataRow::~DataRow() {}

// ============================================================================

bool operator < (const DataRow& row1, const DataRow& row2) {
  if (row1.m_sheet < row2.m_sheet) return true;
  if (row1.m_sheet > row2.m_sheet) return false;
  if (row1.m_id1 < row2.m_id1) return true;
  if (row1.m_id1 > row2.m_id1) return false;
  if (row1.m_id2 < row2.m_id2) return true;
  if (row1.m_id2 > row2.m_id2) return false;
  if (row1.m_id3.solid < row2.m_id3.solid) return true;
  if (row1.m_id3.solid > row2.m_id3.solid) return false;
  if (row1.m_id4.solid < row2.m_id4.solid) return true;
  return false;
}


bool operator == (const DataRow& row1, const DataRow& row2) {
  if (row1.m_sheet != row2.m_sheet) return false;
  if (row1.m_id1 != row2.m_id1) return false;
  if (row1.m_id2 != row2.m_id2) return false;
  if (row1.m_id3.solid != row2.m_id3.solid) return false;
  if (row1.m_id4.solid != row2.m_id4.solid) return false;
  return true;
}

// getters/setters ============================================================

unsigned long  DataRow::getSheet() const {
  return m_sheet;
}


const QString DataRow::getString() const {
  return m_string;
}


const QString DataRow::getFullString() const {
  return QString("%1 %2 %3 %4 %5 ").arg(m_sheet).arg(m_id1).arg(m_id2).arg(m_id3.solid).arg(m_id4.solid) + m_string;
}

void DataRow::setString(const QString &string) {
  m_string = string;
}

// public methods =============================================================

bool DataRow::isCyrillic() {
  for (int i = 0; i < m_string.size(); i++) {
    QChar symbol = m_string.at(i);
    if (symbol.unicode() >= CYR_BEG_CODE && symbol.unicode() <= CYR_END_CODE) {
      return true;
    }
  }
  return false;
}


bool DataRow::isLink() {
  if (m_string.indexOf("http") == 0) return true;
  return false;
}


// read from input stream (binary mode)
void DataRow::readBinDataFrom(QDataStream& input) {
  try {
    ReadDataFromStream(input, m_size);
    ReadDataFromStream(input, m_sheet);
    ReadDataFromStream(input, m_id1);
    ReadDataFromStream(input, m_id2);
    ReadDataFromStream(input, m_id3.split[0]);
    ReadDataFromStream(input, m_id4.split[0]);
    char16_t wch;
    for (size_t i = 0; i < static_cast<int>(m_size); i++) {
      ReadDataFromStream(input, wch);
      if (wch == CR_CODE) continue;                  // skip CR if exist
      if (wch == LF_CODE) m_string.push_back("\\n"); // replace LF to '\n'
      else m_string.push_back(wch);
    }
    // read four null bytes
    ReadDataFromStream(input, wch);
    ReadDataFromStream(input, wch);
  }
  catch (const std::ios_base::failure &err) { throw err; }
  catch (...) { throw false; }
}


// write to out stream (binary mode)
void DataRow::writeBinDataTo(QDataStream& output) {
  QRegularExpression reppat("\\\\n");
  m_string.replace(reppat, "\n"); // replace '\n' to LF
  try {
    m_size = static_cast<unsigned long>(m_string.count());
    WriteDataToStream(output, m_size);
    WriteDataToStream(output, m_sheet);
    WriteDataToStream(output, m_id1);
    WriteDataToStream(output, m_id2);
    WriteDataToStream(output, m_id3.split[0]);
    WriteDataToStream(output, m_id4.split[0]);
    char16_t wch;
    for (int i = 0; i < static_cast<int>(m_size); i++) {
      wch = static_cast<char16_t>(m_string[i].unicode());
      WriteDataToStream(output, wch);
    }
    // write four null bytes
    wch = 0x0000;
    WriteDataToStream(output, wch);
    WriteDataToStream(output, wch);
  }
  catch (const std::ios_base::failure &err) { throw err; }
  catch (...) { throw false; }
}


// read from in stream (text mode)
void DataRow::readTextDataFrom(QTextStream& input) {
  try {
    input >> m_sheet;
    input >> m_id1;
    input >> m_id2;
    input >> m_id3.solid;
    input >> m_id4.solid;
    input.readLineInto(&m_string);

    if (input.status() == QTextStream::ReadCorruptData) throw std::ios_base::failure("read data from file was failed.");

    // formating string
    QRegularExpression rempat("(^\t\"|\r|\"$)");
    m_string.remove(rempat); // remove tabulation, quotes, CR
  }
  catch (const std::ios_base::failure &err) { throw err; }
  catch (...) { throw false; }
}


// write to out stream (text mode)
void DataRow::writeTextDataTo(QTextStream& output) {
  try {
    output << m_sheet << '\t';
    output << m_id1 << '\t';
    output << m_id2 << '\t';
    output << m_id3.solid << '\t';
    output << m_id4.solid << '\t';
    output << '"' << m_string << '"' << '\n';

    if (output.status() == QTextStream::WriteFailed) throw std::ios_base::failure("write data from file was failed.");
  }
  catch (const std::ios_base::failure &err) { throw err; }
  catch (...) { throw false; }
}
