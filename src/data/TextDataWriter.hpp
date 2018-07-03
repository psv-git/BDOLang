#ifndef TEXTDATAWRITER_HPP
#define TEXTDATAWRITER_HPP

#include "ApplicationGlobal.hpp"
#include "DataRow.hpp"


class TextDataWriter : public QObject {
Q_OBJECT

public:
  explicit TextDataWriter(QVector<DataRow*>& from, QTextStream& to);
  ~TextDataWriter();

  bool isComplete();
  bool isError();
  int getProgress();

public slots:
  void process();

private:
  QVector<DataRow*> *m_from = nullptr;
  QTextStream *m_to = nullptr;

  QMutex m_lock;
  bool m_isError = false;
  bool m_isComplete = false;
  qint64 m_counter = 0;
  qint64 m_maxCount = 0;
  int m_currentProgress = 0;

};


#endif // TEXTDATAWRITER_HPP
