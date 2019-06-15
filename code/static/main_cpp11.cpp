#include "static_cpp11.h"
#include <iostream>

int aa;            // global uninitialized (B: bss)
int bb = 14;       // global initialized (D: data)
static int c;      // static uninitialized (b: bss)
static int d = 1;  // static initialized (d: data)
// static const int e; // uninitialized const ‘e’ [-fpermissive]
static const int f = 2;  // static const (r: rodata)
extern int g;      // If unused will not be present in symbol table
extern int h = 3;

int S::S_uninit_a = 1;
const int S::S_const_uninit_e = 5;

int main() {
  std::cout << aa << ' ' << bb << std::endl;
  std::cout << "S{" << std::endl;
  std::cout << "S::S_uninit_a = " << S::S_uninit_a << std::endl;
  // std::cout << "S::b = " << S::b << std::endl;
  // std::cout << "S::c = " << S::c << std::endl;
  // std::cout << "S::d = " << S::d << std::endl;
  std::cout << "S::S_const_uninit_e = " << S::S_const_uninit_e << std::endl;
  std::cout << "S::S_const_init_f = " << S::S_const_init_f << std::endl;
  std::cout << "S::S_constexpr_init_h = " << S::S_constexpr_init_h << std::endl;
  std::cout << "}" << std::endl;
  return 0;
}
