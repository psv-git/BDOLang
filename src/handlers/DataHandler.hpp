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
  SettingsHandler *settingsHandler = nullptr;
  ErrorHandler *errorHandler = nullptr;
  QString fromFilePath;
  QString toFilePath;
  MODE mode;

  bool process(const QString &fromFilePath,  const QString &toFilePath, MODE mode);

  bool readDataFromBinStream(QDataStream& from, QVector<DataRow*>& to);
  void writeDataToBinStream(QVector<DataRow*>& from, QDataStream& to);
  void readDataFromTextStream(QTextStream& from, QVector<DataRow*>& to);
  void writeDataToTextStream(QVector<DataRow*>& from, QTextStream& to);
  void deleteData(QVector<DataRow*>& dataRowsContainer);
  void mergeData(QVector<DataRow*>& from, QVector<DataRow*>& to);
  bool decryptData(QDataStream& from, QVector<DataRow*>& to);
  bool uncompressData(QDataStream& from, QDataStream& to);
  bool encryptData(QVector<DataRow*>& from, QDataStream& to);
  bool compressData(QDataStream& from, QDataStream& to);

};


#endif // DATAHANDLER_HPP
