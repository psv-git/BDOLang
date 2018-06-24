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

  bool operator < (const DataRow& row) const;

  unsigned long  getSheet() const;
  unsigned long  getId1()   const;
  unsigned short getId2()   const;
  unsigned short getId3()   const;
  unsigned short getId4()   const;

  void readBinDataFrom(QDataStream& input);
  void writeBinDataTo(QDataStream& output);
  void readTextDataFrom(QTextStream& input, MODE mode);
  void writeTextDataTo(QTextStream& output);

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
