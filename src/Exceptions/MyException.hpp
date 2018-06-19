#ifndef MYEXCEPTION_HPP
#define MYEXCEPTION_HPP

#include "CPPHeaders.hpp"


class MyException : public std::exception {

public:
  MyException(const std::string& message = "") noexcept;
  ~MyException();

  const char* what() const throw ();

private:
  std::string exceptionMessage;

};


#endif // MYEXCEPTION_HPP
