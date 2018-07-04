#ifndef DATACOMPRESSOR_HPP
#define DATACOMPRESSOR_HPP


#include "ApplicationGlobal.hpp"
#include "DataRow.hpp"


class DataCompressor : public QObject {
Q_OBJECT

public:
  explicit DataCompressor(QDataStream& from, QDataStream& to, PROCESS_MODE mode);
  ~DataCompressor();

  void init();

  bool isComplete() const;
  bool isError() const;
  int getProgress() const;

public slots:
  void process();

private:
  PROCESS_MODE m_mode = PROCESS_MODE::NONE;
  QDataStream *m_from = nullptr;
  QDataStream *m_to = nullptr;

  bool m_isInit = false;
  bool m_isComplete = false;
  bool m_isError = false;

  unsigned int m_buffSize = 16384;
  uint8_t *m_inBuff = nullptr;
  uint8_t *m_outBuff = nullptr;
  z_stream m_stream = { 0 };

  unsigned long m_expectedUncompressedDataSize = 0;
  unsigned long m_uncompressedDataSize = 0;
  unsigned long m_percentValue = 0;
  int m_currentProgress = 0;

  void compressing();
  void uncompressing();

};


#endif // DATACOMPRESSOR_HPP
