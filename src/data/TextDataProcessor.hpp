// Copyright (c) 2018 PSV LGPL-3.0
// https://github.com/psv-git

#ifndef TEXTDATAPROCESSOR_HPP
#define TEXTDATAPROCESSOR_HPP

#include "GlobalClasses.hpp"

class DataRow;


class TextDataProcessor : public QObject {
Q_OBJECT

public:
  explicit TextDataProcessor(QTextStream& stream, QVector<DataRow*>& data, PROCESS_MODE mode);
  ~TextDataProcessor();

  bool isComplete() const;
  bool isError() const;
  int getProgress() const;

public slots:
  void process();

private:
  PROCESS_MODE m_mode = PROCESS_MODE::NONE;
  QTextStream *m_stream = nullptr;
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


#endif // TEXTDATAWRITER_HPP
