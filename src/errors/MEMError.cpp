#include "MEMError.hpp"


MEMError::MEMError(const QString &message) : message(message) {}


MEMError::~MEMError() {}

// public methods =============================================================

const QString& MEMError::what() const {
  return message;
}
