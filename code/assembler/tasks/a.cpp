#include <iostream>

class A {
  virtual ~A() = default;
};

class B {
  virtual ~B() = default;
};

int main() {
  std::cout << sizeof(A) << " " << sizeof(B) << std::endl;
  return 0;
}
