#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include "tools.h"

struct A {
  int a{0x0a};
  virtual void Print() {
    std::cout << "A(a=" << a << ")" << std::endl;
  }
  virtual ~A() = default;
};

struct B: A {
  int b{0x0b};
  virtual void Print() {
    std::cout << "B(b=" << b << ")" << std::endl;
  }
};

struct C: B {
  int c{0x0c};
  virtual void Print() {
    std::cout << "C(d=" << c << ")" << std::endl;
  }
};

struct AA {
  int aa{0xaa};
};

struct D: AA, C {
  int d{0x0d};
};

int main() {
  A a;
  B b;
  C c;
  D d;
  PrintMemoryLayout("A", a);
  PrintMemoryLayout("B", b);
  PrintMemoryLayout("C", c);
  PrintMemoryLayout("D", d);;
  C* rc_ptr_to_C = reinterpret_cast<C*>(&d);
  C* sc_ptr_to_C = static_cast<C*>(&d);
  C* dc_ptr_to_C = dynamic_cast<C*>(&d);
  PrintMemoryLayout("C=*reinterpret_cast<C*>(&d)", *rc_ptr_to_C);
  PrintMemoryLayout("C=*static_cast<C*>(&d)", *sc_ptr_to_C);
  PrintMemoryLayout("C=*dynamic_cast<C*>(&d)", *dc_ptr_to_C);
}
