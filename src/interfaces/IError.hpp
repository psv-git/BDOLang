#ifndef IERROR_HPP
#define IERROR_HPP

#include "headers.hpp"


class IError {

public:
  virtual const QString& what() const = 0;

};


#endif // IERROR_HPP
