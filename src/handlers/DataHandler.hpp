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
  void runned();
  void stopped();
  void failed();

  void started(const QString &msg);
  void progressed(int value);
  void completed();

public slots:
  void run();

private:
  QWidget *m_parent;
  SettingsHandler *m_settingsHandler = nullptr;
  ErrorHandler *m_errorHandler = nullptr;
  QString m_fromFilePath;
  QString m_toFilePath;
  MODE m_mode;

  bool process(const QString &fromFilePath,  const QString &toFilePath, MODE mode);

  bool readDataFromBinStream(QDataStream& from, QVector<DataRow*>& to);
  bool writeDataToBinStream(QVector<DataRow*>& from, QDataStream& to);
  bool readDataFromTextStream(QTextStream& from, QVector<DataRow*>& to);
  bool writeDataToTextStream(QVector<DataRow*>& from, QTextStream& to);
  void deleteData(QVector<DataRow*>& dataRowsContainer);
  bool mergeData(QVector<DataRow*>& from, QVector<DataRow*>& to);
  bool decryptData(QDataStream& from, QVector<DataRow*>& to);
  bool uncompressData(QDataStream& from, QDataStream& to);
  bool encryptData(QVector<DataRow*>& from, QDataStream& to);
  bool compressData(QDataStream& from, QDataStream& to);

};


#endif // DATAHANDLER_HPP
