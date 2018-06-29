#include "IOError.hpp"


IOError::IOError(const QString &message) : message(message) {}


IOError::~IOError() {}

// public methods =============================================================

const QString& IOError::what() const {
  return message;
}
