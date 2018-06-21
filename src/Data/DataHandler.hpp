#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include "CPPDeclarations.hpp"

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
  void readDataFromBinFile(std::fstream& input);
  // write data rows to compressed output bin file
  void writeDataToBinFile(std::fstream& output);

  // read data rows from input text file (BOM_UTF16LE)
  void readDataFromTextFile(u16ifstream& input);
  // write data rows to output text file (BOM_UTF16LE)
  void writeDataToTextFile(u16ofstream& output);

};


#endif // DATAHANDLER_HPP
