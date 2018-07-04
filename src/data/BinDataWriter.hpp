#ifndef BINDATAWRITER_HPP
#define BINDATAWRITER_HPP


#include "ApplicationGlobal.hpp"
class DataRow;


class BinDataWriter : public QObject {
Q_OBJECT

public:
  explicit BinDataWriter(QVector<DataRow*>& from, QDataStream& to);
  ~BinDataWriter();

  bool isComplete() const;
  bool isError() const;
  int getProgress() const;

public slots:
  void write();

private:
  QVector<DataRow*> *m_from = nullptr;
  QDataStream *m_to = nullptr;

  QMutex m_lock;
  bool m_isError = false;
  bool m_isComplete = false;
  qint64 m_counter = 0;
  qint64 m_maxCount = 0;
  int m_currentProgress = 0;

};


#endif // BINDATAWRITER_HPP
