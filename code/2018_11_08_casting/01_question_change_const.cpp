#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include "tools.h"


int main() {
  volatile const int a = 10;
  const int b = 5;
  std::cout << "sizeof(volaitle const int) = " << sizeof(a) << std::endl;
  std::cout << "sizeof(const int) = " << sizeof(b) << std::endl;

  int* a_ptr = const_cast<int*>(&a);
  int* b_ptr = const_cast<int*>(&b);
  std::cout << "Printing addresses of variables:\n" <<
            << "&a = " << (void*)&a << "; " << "a_ptr = " << (void*)a_ptr << '\n'
            << "&b = " << (void*)&b << "; " << "b_ptr = " << (void*)b_ptr << std::endl;
  std::cout << "Before assignment:\n"
  std::cout << "a      = " << a << "; *a_ptr = " << *a_ptr << '\n'
            << "b      = " << b << "; *b_ptr = " << *b_ptr << '\n';
  // Assignment of const values
  *a_ptr = 11;
  *b_ptr = 6;
  // Printing results
  std::cout << "a      = " << a << "; " << "*a_ptr = " << *a_ptr << '\n'
            << "b      = " << b << "; " << "*b_ptr = " << *b_ptr << std::endl;
  return 0;
}
