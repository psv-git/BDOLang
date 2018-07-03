#include "TextDataReader.hpp"
#include "DataRow.hpp"


TextDataReader::TextDataReader(QObject *parent) : QObject(parent) {}


TextDataReader::~TextDataReader() {}

// ============================================================================

// read data rows from input text file
void TextDataReader::readDataFromStream(QTextStream& from, QVector<DataRow*>& to) {
  if (!isInit) {
    from.device()->seek(0);
    from.resetStatus();
    from.setAutoDetectUnicode(true);
    from.skipWhiteSpace();
    isInit = true;
    fullSize = from.device()->size();
  }

  try {
    DataRow* dataRow = new DataRow();
    if (!dataRow->readTextDataFrom(from)) throw false;
    qint64 currentSize = from.device()->pos();
    emit sendProgress(static_cast<int>(currentSize / fullSize));
    to.push_back(dataRow);
    if (from.atEnd()) emit sendEndOfStream();
  }
  catch (std::bad_alloc) {
    ErrorHandler::getInstance().addErrorMessage("In function \"DataHandler::readDataFromTextStream\" allocating memory was failed.");
    throw std::runtime_error("read data from text stream was failed.");
  }
  catch (...) {
    throw std::runtime_error("read data from text stream was failed.");
  }
}
