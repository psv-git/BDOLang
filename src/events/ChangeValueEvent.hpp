#ifndef CHANGEVALUEEVENT_HPP
#define CHANGEVALUEEVENT_HPP

#include "headers.hpp"


class ChangeValueEvent : public QEvent {

public:
  ChangeValueEvent(int value);
 ~ChangeValueEvent();

  int getValue() const;

private:
  int value;

};

#endif // CHANGEVALUEEVENT_HPP
