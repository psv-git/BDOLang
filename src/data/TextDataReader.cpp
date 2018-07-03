#include "TextDataReader.hpp"
#include "DataRow.hpp"


TextDataReader::TextDataReader(QTextStream& from, QVector<DataRow*>& to) {
  TextDataReader::from = &from;
  TextDataReader::to = &to;

  from.device()->seek(0);
  from.resetStatus();
  from.setAutoDetectUnicode(true);
  from.skipWhiteSpace();
  fullSize = from.device()->size();
}


TextDataReader::~TextDataReader() {}

// ============================================================================

bool TextDataReader::isComplete() {
  QMutexLocker locker(&lock);
  return complete;
}


int TextDataReader::getProgress() {
  return progress;
}


void TextDataReader::process() {
  QMutexLocker locker(&lock);
  DataRow* dataRow = new DataRow();
  if (!dataRow->readTextDataFrom(*from)) throw false;
  to->push_back(dataRow);
  qint64 currentSize = from->device()->pos();
  progress = (100 * currentSize) / fullSize;
  if (from->atEnd()) complete = true;
}
