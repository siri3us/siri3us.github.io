#include <iostream>
#include <cstdio>

void MakeSomethingBad() {
  throw 1;
}

struct S {
  S() {};

  S(int value) : value_(value) {};

  S(const S&) throw() {
    puts("Now we will make something bad");
    S s;
    MakeSomethingBad();
  }

  ~S() { puts("~S()"); }

  int value_{0};
};

int main(int argc, char **argv) {
  S s1(12);
  S s2(13);
  S s3(s2);
  return 0;
}
