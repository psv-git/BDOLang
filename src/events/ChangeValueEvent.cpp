#include "ChangeValueEvent.hpp"


ChangeValueEvent::ChangeValueEvent(int value) : QEvent(QEvent::User) {
  ChangeValueEvent::value = value;
}


ChangeValueEvent::~ChangeValueEvent() {}

// ============================================================================

int ChangeValueEvent::getValue() const {
  return value;
}
