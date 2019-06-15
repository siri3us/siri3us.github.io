#include <iostream>
#include "integer_value.h"

int main(int argc, char *argv[]) {
  int result = 0;
  try {
    IntegerValue var1{5};
    IntegerValue var2{100};
    result = (var1.GetValue() + var2.GetValue() > 0) ? 0 : -1;
  } catch (...) {
    result = -1;
    std::cerr << "Error happended!" << std::endl;
  }
  return result;
}
