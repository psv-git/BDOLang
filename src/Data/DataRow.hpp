#ifndef DATAROW_HPP
#define DATAROW_HPP

#include "ApplicationFunctions.hpp"


union uint8_16 {
  unsigned short solid;
  uint8_t split[2];
};


class DataRow {

public:
  DataRow();
  ~DataRow();

  friend bool operator < (const DataRow& row1, const DataRow& row2);
  friend bool operator == (const DataRow& row1, const DataRow& row2);

  unsigned long getSheet() const;
  const QString getString() const;

  void setString(const QString &string);

  void readBinDataFrom(QDataStream& input);
  void writeBinDataTo(QDataStream& output);
  void readTextDataFrom(QTextStream& input);
  void writeTextDataTo(QTextStream& output);

private:
  unsigned long m_size = 0;
  unsigned long m_sheet = 0;
  unsigned long m_id1 = 0;
  unsigned short m_id2 = 0;
  uint8_16 m_id3 = { 0 };
  uint8_16 m_id4 = { 0 };

  QString m_string;

};


#endif // DATAROW_HPP
