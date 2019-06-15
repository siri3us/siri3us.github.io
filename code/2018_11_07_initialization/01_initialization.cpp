#include <iostream>
#include <complex>

void function1() {
  int i1;
  int i2 = 42;
  int i3 = 59.2;
  unsigned int ui1 = -1;
  std::cout << "i1 = " << i1 << "\ni2 = " << i2 << "\ni3 = " << i3 << "\nui1 = " << ui1 << std::endl;
}

void function2() {
  std::complex<double> c(1.0, 2.0);
  int i4(59.2);
  int i5 = int();
  std::cout << "i4 = " << i4 << "\ni5 = " << i5 << "\nc = (" << c.real() << ", " << c.imag() << ")" << std::endl;
}

int main() {
  function1();
  function2();
  return 0;
}
