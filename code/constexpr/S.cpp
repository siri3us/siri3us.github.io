#include <iostream>

struct S {
  S() = default;
  S(const S&) = default;
  S(S&&) = delete;
  ~S() = default;
  S& operator=(const S&) = default;
  S& operator=(S&&) = default;
};

int main() {
  S s1;
  S s2 = std::move(s1);
  return 0;
}
