#ifndef TEXTDATAREADER_HPP
#define TEXTDATAREADER_HPP

#include "ApplicationGlobal.hpp"
#include "DataRow.hpp"


class TextDataReader : public QObject {
Q_OBJECT

public:
  explicit TextDataReader(QTextStream& from, QVector<DataRow*>& to);
  ~TextDataReader();

  bool isComplete() const;
  bool isError() const;
  int getProgress() const;

public slots:
  void read();

private:
  QTextStream *m_from = nullptr;
  QVector<DataRow*> *m_to = nullptr;

  QMutex m_lock;
  bool m_isError = false;
  bool m_isComplete = false;
  int m_currentProgress = 0;
  qint64 m_fullSize = 0;

};


#endif // TEXTDATAREADER_HPP
