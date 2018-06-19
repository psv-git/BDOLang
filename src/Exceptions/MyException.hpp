#ifndef MYEXCEPTION_HPP
#define MYEXCEPTION_HPP

#include "../Global/CPPHeaders.hpp"


class MyException : public std::exception {

public:
  MyException(const std::string& message = "", uint8_t code = 0) noexcept;
  ~MyException();

  const char* what() const throw ();
  const char* getMessage() const;
  uint8_t getCode() const;

private:
  uint8_t exceptionCode;
  std::string exceptionMessage;

};

#endif // MYEXCEPTION_HPP
