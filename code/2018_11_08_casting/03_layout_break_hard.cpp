#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include "tools.h"

struct A {
  int a{0x0a};
  virtual void Print() {
    std::cout << "A(a=" << std::dec << a << ")" << std::endl;
  }
  virtual ~A() = default;
};

struct B: A {
  int b{0x0b};
  virtual void Print() {
    std::cout << "B(b=" << std::dec << b << ")" << std::endl;
  }
};

int main() {
  // Step 1. Figure out how objects are orgainzed in memory
  A a;
  B b;
  PrintMemoryLayout("A", a);
  PrintMemoryLayout("B", b);
  // Step 2. Get vtable addresses
  uintptr_t a_vtable_ptr = GetVtableAddress(a);
  uintptr_t b_vtable_ptr = GetVtableAddress(b);
  std::cout << "vtable address of A = " << reinterpret_cast<void*>(a_vtable_ptr) << std::endl;
  std::cout << "vtable address of B = " << reinterpret_cast<void*>(b_vtable_ptr) << std::endl;
  // Step 3. Change a to become b
  std::cout << "Changing vtable address of variable 'a'..." << std::endl;
  // ChangeVtableAddress(a, b_vtable_ptr);
  PrintMemoryLayout("A", a);
  reinterpret_cast<B&>(a).Print();
  b.Print();
}
