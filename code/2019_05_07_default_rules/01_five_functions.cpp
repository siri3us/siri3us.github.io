#include <iostream>
#include <cstdio>
#include <vector>
#include "print_traits.h"

#ifdef NOEXCEPT_ALL
#define NOEXCEPT_ noexcept
#define NOEXCEPT_MOVE_
#else
#define NOEXCEPT_
#ifdef NOEXCEPT_MOVE
#define NOEXCEPT_MOVE_ noexcept
#else
#define NOEXCEPT_MOVE_
#endif
#endif

struct S {
  S() NOEXCEPT_ = default;

  explicit S(int value) NOEXCEPT_ : value_(value) {
    puts("S(int)");
  }

  ~S() {
    puts("~S()");
  }

  S(const S& rhs) NOEXCEPT_ : value_(rhs.value_) {
    puts("S(const S&)");
  }

  S& operator=(const S& rhs) NOEXCEPT_ {
    puts("S& operator=(const S&)");
    value_ = rhs.value_;
    return *this;
  }

  S(S&& rhs) NOEXCEPT_MOVE_ {
    puts("S(S&&)");
    value_ = rhs.value_;
  }

  S& operator=(S&& rhs) NOEXCEPT_MOVE_ {
    puts("S& operator=(S&&)");
    value_ = rhs.value_;
    return *this;
  }

  int value_{0};
};

int main() {
  PrintClassTraits<S>();

  S s1{15};
  S s2 = s1;
  [[maybe_unused]] S s3 = std::move(s2);
  s1 = s3;
  s2 = std::move(s1);

  auto values = TestVectorPushBack<S>(s1, 5);
  return 0;
}
