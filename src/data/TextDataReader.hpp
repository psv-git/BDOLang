#ifndef TEXTDATAREADER_HPP
#define TEXTDATAREADER_HPP

#include "ApplicationGlobal.hpp"
#include <QMutex>

class DataRow;


class TextDataReader : public QObject {
Q_OBJECT

public:
  explicit TextDataReader(QTextStream& from, QVector<DataRow*>& to);
  ~TextDataReader();

  bool isComplete();
  int getProgress();

signals:

public slots:
  void process();

private:
  QTextStream *from = nullptr;
  QVector<DataRow*> *to = nullptr;

  QMutex lock;
  bool complete = false;
  int progress = 0;
  qint64 fullSize = 0;

};


#endif // TEXTDATAREADER_HPP
