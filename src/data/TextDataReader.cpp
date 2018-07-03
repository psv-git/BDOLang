#include "TextDataReader.hpp"

TextDataReader::TextDataReader(QObject *parent) : QObject(parent)
{

}


// read data rows from input text file
void DataHandler::readDataFromTextStream(QTextStream& from, QVector<DataRow*>& to) {
  from.device()->seek(0);
  from.resetStatus();
  from.setAutoDetectUnicode(true);
  from.skipWhiteSpace();

  try {
    qint64 fullSize = from.device()->size();
    DataRow* dataRow = new DataRow();
    if (!dataRow->readTextDataFrom(from)) throw false;
    qint64 currentSize = from.device()->pos();
//      emit progressed(static_cast<int>(currentSize / fullSize)); // TODO:
    ChangeValueEvent *event = new ChangeValueEvent(currentSize / fullSize);
    QCoreApplication::postEvent(parent, event);
    to.push_back(dataRow);
    if (from.atEnd()) emit stop();
  }
  catch (std::bad_alloc) {
    errorHandler->addErrorMessage("In function \"DataHandler::readDataFromTextStream\" allocating memory was failed.");
    throw std::runtime_error("read data from text stream was failed.");
  }
  catch (...) {
    throw std::runtime_error("read data from text stream was failed.");
  }
}
