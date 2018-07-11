// Copyright (c) 2018 PSV
// https://github.com/psv-git

#ifndef FILEFILLER_HPP
#define FILEFILLER_HPP

#include "GlobalClasses.hpp"


class FileFiller : public QObject {
Q_OBJECT

public:
  explicit FileFiller(QDataStream& from, QDataStream& to);
  ~FileFiller();

  bool isComplete() const;
  bool isError() const;
  int getProgress() const;

public slots:
  void process();

private:
  QDataStream *m_from = nullptr;
  QDataStream *m_to = nullptr;

  bool m_isError = false;
  bool m_isComplete = false;

  qint64 m_stepCounter = 0;
  qint64 m_stepCount = 0;
  qint64 m_percentValue = 0;
  int m_currentProgress = 0;

  void fill();

};


#endif // FILEFILLER_HPP
