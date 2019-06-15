#include <cstdio>
#include <iostream>

#include "sum.h"
#include "mult.h"

int main() {
  double result1 = Mult(1, 2);
  double result2 = Sum(2, 1);
  std::cout << result1 << ' ' << result2 << std::endl;
  return 0;
}
