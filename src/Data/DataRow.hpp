#ifndef DATAROW_HPP
#define DATAROW_HPP

#include "CPPHeaders.hpp"


class DataRow {

public:
  DataRow();
  ~DataRow();

  bool operator < (const DataRow& row) const;
  friend std::fstream& operator >> (std::fstream& input, DataRow& row);
  friend std::wofstream& operator << (std::wofstream& output, DataRow& row);
  friend std::fstream& operator << (std::fstream& output, DataRow& row);

private:
  uint32_t size;
  uint32_t type;
  uint32_t id1;
  uint16_t id2;
  uint8_t id3;
  uint8_t id4;

  std::wstring string;

};


#endif // DATAROW_HPP
