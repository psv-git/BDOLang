#ifndef DATAROW_HPP
#define DATAROW_HPP

#include "ApplicationFunctions.hpp"


class DataRow {

public:
  DataRow();
  ~DataRow();

  void readBinDataFrom(QDataStream& input);
  void writeBinDataTo(QDataStream& output);
  void readTextDataFrom(QTextStream& input);
  void writeTextDataTo(QTextStream& output);

private:
  unsigned long  size = 0;
  unsigned long  type = 0;
  unsigned long  id1  = 0;
  unsigned short id2  = 0;
  unsigned short id3  = 0;
  unsigned short id4  = 0;

  QString string;

};


#endif // DATAROW_HPP
