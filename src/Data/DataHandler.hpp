#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include "../Global/Global.hpp"

class DataRow;


class DataHandler {

public:
  DataHandler();
  ~DataHandler();

  // read data rows from compressed input binary file
  void readDataFromBinFile(std::ifstream& input);
  // write data rows to output text file (BOM_UTF16LE)
  void writeDataToTextFile(std::wofstream& output);
  // write data rows to compressed output bin file
  void writeDataToBinFile(std::fstream& output);
  // get used memory
  size_t getUsedMemory() const;

private:
  std::vector<DataRow*> dataRowsContainer;
  size_t usedMemory; // MB

  // void sortData();

};

#endif // DATAHANDLER_HPP