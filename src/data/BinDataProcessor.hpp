// Copyright (c) 2018 PSV
// https://github.com/psv-git

#ifndef BINDATAPROCESSOR_HPP
#define BINDATAPROCESSOR_HPP


#include "GlobalClasses.hpp"

class DataRow;


class BinDataProcessor : public QObject {
Q_OBJECT

public:
  explicit BinDataProcessor(QDataStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode);
  ~BinDataProcessor();

  bool isComplete() const;
  bool isError() const;
  int getProgress() const;

public slots:
  void process();

private:
  PROCESS_MODE m_mode = PROCESS_MODE::NONE;
  QDataStream *m_stream = nullptr;
  QVector<DataRow*> *m_data = nullptr;

  bool m_isError = false;
  bool m_isComplete = false;

  qint64 m_stepCounter = 0;
  qint64 m_stepCount = 0;
  qint64 m_percentValue = 0;
  int m_currentProgress = 0;

  void read();
  void write();

};


#endif // BINDATAWRITER_HPP
