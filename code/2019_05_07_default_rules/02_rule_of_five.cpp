#include <iostream>
#include <cstdio>
#include "print_traits.h"

#ifdef NOEXCEPT_ALL
#define NOEXCEPT_ noexcept
#define NOEXCEPT_MOVE_ noexcept
#else
#define NOEXCEPT_
#ifdef NOEXCEPT_MOVE
#define NOEXCEPT_MOVE_ noexcept
#else
#define NOEXCEPT_MOVE_
#endif
#endif

struct A {
  // Everything is set to noexcept to model the automatic code generation
  A() NOEXCEPT_ {
    puts("A()");
  }
  A(const A&) NOEXCEPT_ {
    puts("A(const A&)");
  }
  A(A&&) NOEXCEPT_ {
    puts("A(A&&)");
  }

  A& operator=(const A&) NOEXCEPT_MOVE_ {
    puts("A& operator=(const A&)");
    return *this;
  }
  A& operator=(A&&) NOEXCEPT_MOVE_ {
    puts("A& operator=(A&&)");
    return *this;
  }

  // Noexcept here is not necessary
  ~A() noexcept {
    puts("~A()");
  }
};

struct S {
  S() {
    puts("S()");
  }

  S(int) {
    puts("S(int)");
  }

  ~S() {
    puts("~S()");
  }

  S(const S& rhs) : a_(rhs.a_) {
    puts("S(const S&)");
  }

  S& operator=(const S& rhs) {
    a_ = rhs.a_, puts("S& operator=(const S&)");
    return *this;
  }

  S(S&& rhs) : a_(std::move(rhs.a_)) {
    puts("S(S&&)");
  }
  S& operator=(S&& rhs) {
    a_ = std::move(rhs.a_);
    puts("S& operator=(S&&)");
    return *this;
  }

  A a_;
};

int main() {
  PrintClassTraits<S>();

  S s1;                  // Default construction
  S s2 = s1;             // Copy construction
  S s3 = std::move(s1);  // Move construction
  s2 = s1;               // Copy assignment
  s3 = std::move(s1);    // Move assignment

  auto vec = TestVectorPushBack<S>(s1, 5);
  return 0;
}
