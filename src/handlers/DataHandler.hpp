#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include "ApplicationGlobal.hpp"

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

  bool cryptProcessing(QDataStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode);
  bool binProcessing(QDataStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode);
  bool textProcessing(QTextStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode);
  bool mergeProcessing(QVector<DataRow*>& from, QVector<DataRow*>& to);
  bool compressProcessing(QDataStream& from, QDataStream& to, PROCESS_MODE mode);

  void deleteData(QVector<DataRow*>& dataRowsContainer);

};


#endif // DATAHANDLER_HPP
