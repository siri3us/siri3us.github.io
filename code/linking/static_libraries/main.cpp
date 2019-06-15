#include <iostream>
#include "geom.h"
#include "logger.h"

int main() {
  double result1 = Sum(1, 5);
  double result2 = Mult(2, 5);
  std::cout << result1 << ' ' << result2 << std::endl;
  // GetLogger();
  return 0;
}
