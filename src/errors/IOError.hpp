#ifndef IOERROR_HPP
#define IOERROR_HPP

#include "IError.hpp"


class IOError : public IError {

public:
  IOError(const QString &message);
  ~IOError();

  const QString& what() const;

private:
  QString message;

};


#endif // IOERROR_HPP
