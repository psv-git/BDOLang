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
  void mergeTwoFiles(const QString &filePath1, const QString &filePath2);
  //
  void convertBinFileToTextFile(const QString &binFilePath);
  //
  void convertTextFileToBinFile(const QString &textFilePath);

private:
  DataHandler();
  ~DataHandler();

  std::vector<DataRow*> dataRowsContainer;

  // delete existed data
  void resetData();
  // read data rows from compressed input binary file
  void readDataFromBinFile(std::ifstream& input);
  // write data rows to compressed output bin file
  void writeDataToBinFile(std::fstream& output);

  // read data rows from input text file (BOM_UTF16LE)
  void readDataFromTextFile(std::wifstream& input);
  // write data rows to output text file (BOM_UTF16LE)
  void writeDataToTextFile(std::wofstream& output);

};


#endif // DATAHANDLER_HPP
