#ifndef DATAROW_HPP
#define DATAROW_HPP

#include "CPPDeclarations.hpp"


class DataRow {

public:
  DataRow();
  ~DataRow();

//  bool operator < (const DataRow& row) const;
  friend std::fstream& operator >> (std::fstream& input, DataRow& row);
  friend std::fstream& operator << (std::fstream& output, DataRow& row);
  friend std::wifstream& operator >> (std::wifstream& input, DataRow& row);
  friend std::wofstream& operator << (std::wofstream& output, DataRow& row);

private:
  uint32_t size = 0;
  uint32_t type = 0;
  uint32_t id1 = 0;
  uint16_t id2 = 0;
  uint8_16_t id3 = { 0 };
  uint8_16_t id4 = { 0 };

  std::wstring string;

};


#endif // DATAROW_HPP
