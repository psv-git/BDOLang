#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include "CPPHeaders.hpp"

class DataRow;
class QString;


class DataHandler {

public:
  static DataHandler& getInstance() {
    static DataHandler instance;
    return instance;
  }

  DataHandler(DataHandler const&) = delete;
  DataHandler& operator = (DataHandler const&) = delete;

  //
  void mergeTwoFiles(const QString &fileName1, const QString &fileName2);
  //
  void convertBinFileToTextFile(const QString &binFileName);
  // resed existed data
  void resetData();
  //
  bool isDataExist();

private:
  DataHandler();
  ~DataHandler();

  bool dataExist;
  std::vector<DataRow*> dataRowsContainer;

  // read data rows from compressed input binary file
  void readDataFromBinFile(std::ifstream& input);
  // write data rows to output text file (BOM_UTF16LE)
  void writeDataToTextFile(std::wofstream& output);
  // write data rows to compressed output bin file
  void writeDataToBinFile(std::fstream& output);

};


#endif // DATAHANDLER_HPP
