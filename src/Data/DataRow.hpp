#ifndef DATAROW_HPP
#define DATAROW_HPP

#include "ApplicationFunctions.hpp"


union uint8_16 {
  unsigned short solid;
  uint8_t        split[2];
};


class DataRow {

public:
  DataRow();
  ~DataRow();

  friend bool operator <  (const DataRow& row1, const DataRow& row2);
  friend bool operator == (const DataRow& row1, const DataRow& row2);

  unsigned long  getSheet() const;
  const QString getString() const;

  void setString(const QString &string);

  bool readBinDataFrom(QDataStream& input);
  bool writeBinDataTo(QDataStream& output);
  bool readTextDataFrom(QTextStream& input);
  bool writeTextDataTo(QTextStream& output);

private:
  unsigned long  size  = 0;
  unsigned long  sheet = 0;
  unsigned long  id1   = 0;
  unsigned short id2   = 0;
  uint8_16       id3   = { 0 };
  uint8_16       id4   = { 0 };

  QString string;

};


#endif // DATAROW_HPP
