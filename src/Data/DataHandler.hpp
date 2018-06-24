#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include "ApplicationFunctions.hpp"

class DataRow;


class DataHandler {

public:
  DataHandler();
  ~DataHandler();

  void mergeFiles(const QString &fromFilePath,   const QString &toFilePath, MODE mode);
  void convertFile(const QString &fromFilePath, const QString &toFilePath, MODE mode);

private:
  QVector<DataRow*> dataRowsContainer;

  // delete existed data
  void resetData();

  // read data rows from compressed input binary file
  void readDataFromBinStream(QDataStream& input);
  // write data rows to compressed output bin file
  void writeDataToBinStream(QDataStream& output);

  // read data rows from input text file
  void readDataFromTextStream(QTextStream& input, MODE mode);
  // write data rows to output text file
  void writeDataToTextStream(QTextStream& output);

  // decrypt data from input file to data container
  void decryptData(QDataStream& from, QVector<DataRow*>& to);
  // uncompress data from input file to tmp data file
  void uncompressData(QDataStream& from, QDataStream& to);

  // encrypt data to output binary file from data container
  void encryptData(QVector<DataRow*>& from, QDataStream& to);
  // compress binary tmp data file to binary output file
  void compressData(QDataStream& from, QDataStream& to);

};


#endif // DATAHANDLER_HPP
