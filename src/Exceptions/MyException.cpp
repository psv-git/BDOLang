#include "MyException.hpp"

MyException::MyException(const std::string& msg, uint8_t code) noexcept {
  exceptionMessage = msg;
  exceptionCode = code;
}

MyException::~MyException() {}

const char* MyException::what() const throw () {
  return exceptionMessage.c_str();
}

const char* MyException::getMessage() const {
  return exceptionMessage.c_str();
}

uint8_t MyException::getCode() const {
  return exceptionCode;
}
