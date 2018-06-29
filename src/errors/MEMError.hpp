#ifndef MEMERROR_HPP
#define MEMERROR_HPP

#include "IError.hpp"


class MEMError : public IError {

public:
  MEMError(const QString &message);
  ~MEMError();

  const QString& what() const;

private:
  QString message;

};


#endif // MEMERROR_HPP
