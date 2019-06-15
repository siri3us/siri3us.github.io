#include <iostream>
#include <cstdio>

struct S {
  S() { puts("S()"); };
  S(int value) : value_(value) { puts("S(int)"); };
  ~S() {  // noexcept(false)
    puts("~S()");
    throw "Very very bad practice!";
  }
  int value_{0};
};

void PrintOnTerminate() {
  puts("An exception has not been caught!");
}

int main(int argc, char **argv) {
  std::set_terminate(PrintOnTerminate);
  try {
    S s;
    std::cout << std::boolalpha << "noexcept(s.~S()) = " <<  noexcept(s.~S()) << std::endl;
  } catch (...) {
    puts("An exception has been caught!");
  }
  return 0;
}
