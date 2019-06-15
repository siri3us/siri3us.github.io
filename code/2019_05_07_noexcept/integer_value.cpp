#include "integer_value.h"

IntegerValue::IntegerValue(int value) NOEXCEPT: value_(value) {
}

int IntegerValue::GetValue() const NOEXCEPT {
  return value_;
}

IntegerValue operator+(const IntegerValue& lhs, const IntegerValue& rhs) NOEXCEPT {
  return IntegerValue{lhs.GetValue() + rhs.GetValue()};
}
