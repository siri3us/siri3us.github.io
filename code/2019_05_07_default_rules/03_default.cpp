#include <iostream>
#include <cstdio>

struct A {
  // Everything is set to noexcept to model the automatic code generation
  A() noexcept {
    puts("A()");
  }
  ~A() noexcept {
    puts("~A()");
  }
  A(const A&) noexcept {
    puts("A(const A&)");
  }
  A(A&&) noexcept {
    puts("A(A&&)");
  }
  A& operator=(const A&) noexcept {
    puts("A& operator=(const A&)");
    return *this;
  }
  A& operator=(A&&) noexcept {
    puts("A& operator=(A&&)");
    return *this;
  }
};

struct S {
 public:
  // S() { puts("S()"); }
  ~S() = default;
  // S(int) { puts("S(int)"); }
  // ~S() { puts("~S()"); }
  // S(const S& rhs) : a_(rhs.a_) { puts("S(const S&)"); }
  // S& operator=(const S& rhs) { a_ = rhs.a_, puts("S& operator=(const S&)"); return *this; }
  // S(S&& rhs) : a_(std::move(rhs.a_)) { puts("S(S&&)"); }
  // S& operator=(S&& rhs) { a_ = std::move(rhs.a_); puts("S& operator=(S&&)"); return *this; }

 private:
  A a_;
};

int main() {
  // 1) Everything is default
  S s1;
  S s2 = s1;
  S s3 = std::move(s2);
  s1 = s3;
  s3 = std::move(s2);
  return 0;
}
