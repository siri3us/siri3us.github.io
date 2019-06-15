#include <iostream>
#include <memory>

struct A {
  A() {
    std::cout << "C";
  }

  ~A() {
    std::cout << "D";
  }
};


int main() {
  // std::unique_ptr<A> a(new A[5]);
  std::unique_ptr<A[]> a(new A[5]);
  return 0;
}
