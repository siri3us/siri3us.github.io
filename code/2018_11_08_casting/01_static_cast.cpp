#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include "tools.h"

class A {
 public:
  int a = 0x0a; 
};

class B : public A {
 public:
  int b = 0x0b;
};

class C {
 public:
  int c = 0x0c;
}

int main() {
  long long ll = 10000000000000;
  int i = static_cast<int>(ll);
  
  std::cout << "ll = " << ll << std::endl;
  std::cout << "i  = " << static_cast<int>(ll) << std::endl;
  std::cout << "ui = " << static_cast<unsigned int>(ll) << std::endl;
  return 0;
}
