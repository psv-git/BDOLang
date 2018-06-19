#include "MyException.hpp"


MyException::MyException(const std::string& msg) noexcept {
  exceptionMessage = msg;
}


MyException::~MyException() {}


const char* MyException::what() const throw () {
  return exceptionMessage.c_str();
}
