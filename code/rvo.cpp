#include <cstdio>
#include <utility>

struct S {
  ~S() { puts("~S()"); }
  S() { puts("S()"); }
  S(const S&) { puts("S(const S&)"); }
  S& operator=(const S&) { puts("S& operator=(const S&)"); return *this; }
  S& operator=(S&&) { puts("S& operator=(S&&)"); return *this; }
  S(S&&) { puts("S(S&&)"); }
};

S MakeS1() {
  return S{};
}

S MakeS2() {
  return {};
}

struct B {
  int a;
  S s;
};

B MakeB() {
  return {};
}

S MakeS3() {
  B b;
  return b.s;
}

S MakeS4() {
  return MakeB().s;
}

int main() {
  puts("Creating first");
  [[maybe_unused]] auto s1 = MakeS1();
  puts("Creating second");
  [[maybe_unused]] auto s2 = MakeS2();
  puts("Creating third");
  [[maybe_unused]] auto s3 = MakeS3();
  puts("Creating fourth");
  [[maybe_unused]] auto s4 = MakeS4();
  return 0;
}
