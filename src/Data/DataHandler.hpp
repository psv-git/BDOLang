#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include "ApplicationFunctions.hpp"

class DataRow;


class DataHandler {

public:
  DataHandler();
  ~DataHandler();

  void mergeFiles(const QString &fromFilePath, const QString &toFilePath, MODE mode);
  void convertBinFileToTextFile(const QString &binFilePath,  const QString &textFilePath);
  void convertTextFileToBinFile(const QString &textFilePath, const QString &binFilePath);

private:
  std::vector<DataRow*> dataRowsContainer;

  // delete existed data
  void resetData();

  // read data rows from compressed input binary file
  void readDataFromBinFile(QDataStream& input);
  // write data rows to compressed output bin file
  void writeDataToBinFile(QDataStream& output);

  // read data rows from input text file (BOM_UTF16LE)
  void readDataFromTextFile(QTextStream& input);
  // write data rows to output text file (BOM_UTF16LE)
  void writeDataToTextFile(QTextStream& output);

  // decrypt data from input file to data container
  void decryptFile(QDataStream& from, std::vector<DataRow*>& to);
  // uncompress data from input file to tmp data file
  void uncompressFile(QDataStream& from, QDataStream& to);

  // encrypt data to output binary file from data container
  void encryptFile(std::vector<DataRow*>& from, QDataStream& to);
  // compress binary tmp data file to binary output file
  void compressFile(QDataStream& from, QDataStream& to);

};


#endif // DATAHANDLER_HPP
