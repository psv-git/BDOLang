#ifndef MERGEDATAPROCESSOR_HPP
#define MERGEDATAPROCESSOR_HPP

#include "ApplicationGlobal.hpp"

class DataRow;


class MergeDataProcessor : public QObject {
Q_OBJECT

public:
  explicit MergeDataProcessor(QVector<DataRow*>& from, QVector<DataRow*>& to, LANG sourceLanguage);
  ~MergeDataProcessor();

  bool isComplete() const;
  bool isError() const;
  int getProgress() const;

public slots:
  void process();

private:
  QVector<DataRow*> *m_from = nullptr;
  QVector<DataRow*> *m_to = nullptr;
  LANG m_sourceLanguage = LANG::NONE;

  int m_operationNumber = 1; // trigger to switch operation
  bool m_isError = false;
  bool m_isComplete = false;

  qint64 m_stepCounter = 0;
  qint64 m_stepCount = 0;
  qint64 m_percentValue = 0;
  int m_currentProgress = 0;

  // saveRanges variables
  QMap<unsigned long, QPair<int, int>> m_sheetsPositionsList;
  unsigned long m_sheetValue = 0;
  int m_beg = 0;
  int m_end = 0;

  // replace variables
  int m_index = 0;


  void saveSheetsRanges();
  void replaceTranslation();

};


#endif // MERGEDATAPROCESSOR_HPP
