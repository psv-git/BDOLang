#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include "ApplicationFunctions.hpp"

class DataRow;


class DataHandler : public QObject {
Q_OBJECT

public:
  DataHandler(const QString &fromFilePath, const QString &toFilePath, MODE mode);
  ~DataHandler();

signals:
  void failed();
  void completed();

public slots:
  void start();
  void stop();

private:
  Settings *settings         = nullptr;
  ErrorHandler *errorHandler = nullptr;
  QString fromFilePath;
  QString toFilePath;
  MODE mode;

  bool mergeFiles(const QString &fromFilePath,  const QString &toFilePath, MODE mode);
  bool convertFile(const QString &fromFilePath, const QString &toFilePath, MODE mode);

  void readDataFromBinStream(QDataStream& from, QVector<DataRow*>& to);
  void writeDataToBinStream(QVector<DataRow*>& from, QDataStream& to);
  void readDataFromTextStream(QTextStream& from, QVector<DataRow*>& to);
  void writeDataToTextStream(QVector<DataRow*>& from, QTextStream& to);
  void deleteData(QVector<DataRow*>& dataRowsContainer);
  void mergeData(QVector<DataRow*>& from, QVector<DataRow*>& to);
  void decryptData(QDataStream& from, QVector<DataRow*>& to);
  void uncompressData(QDataStream& from, QDataStream& to);
  void encryptData(QVector<DataRow*>& from, QDataStream& to);
  void compressData(QDataStream& from, QDataStream& to);

};


#endif // DATAHANDLER_HPP
