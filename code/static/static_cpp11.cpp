#include "static_cpp11.h"
#include <iostream>

void S::PrintValues() {
  std::cout << "S{" << std::endl;
  std::cout << "S::S_uninit_a = " << S::S_uninit_a << std::endl;
  // std::cout << "S::b = " << S::b << std::endl;
  // std::cout << "S::c = " << S::c << std::endl;
  // std::cout << "S::d = " << S::d << std::endl;
  std::cout << "S::S_const_uninit_e = " << S::S_const_uninit_e << std::endl;
  std::cout << "S::S_const_init_f = " << S::S_const_init_f << std::endl;
  std::cout << "S::S_constexpr_init_h = " << S::S_constexpr_init_h << std::endl;
  std::cout << "}" << std::endl;
}
