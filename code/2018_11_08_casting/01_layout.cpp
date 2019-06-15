#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include "tools.h"

struct A {
  int a{0x0a};
};

struct B: A {
  int b{0x0b};
};

struct C: B {
  int c{0x0c};
};

struct AA {
  int aa{0xaa};
};

struct D: AA, C {
  int d{0x0d};
};

int main() {
  PrintMemoryLayout("C", C());
  std::cout << std::endl;
  PrintMemoryLayout("D", D());
}
