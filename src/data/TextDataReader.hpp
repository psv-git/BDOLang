#ifndef TEXTDATAREADER_HPP
#define TEXTDATAREADER_HPP

#include "ApplicationGlobal.hpp"


class TextDataReader : public QObject {
Q_OBJECT

public:
  explicit TextDataReader(QObject *parent = nullptr);
  ~TextDataReader();

signals:
  void sendProgress(int val);
  void sendEndOfStream();

public slots:
  void readDataFromStream(QTextStream& from, QVector<DataRow*>& to);

private:
  bool isInit = false;
  qint64 fullSize = 0;

};


#endif // TEXTDATAREADER_HPP
