#include <iostream>


template<int N>
struct StaticLog2 {
  static const int value = StaticLog2<N / 2>::value + 1;
};

template<>
struct StaticLog2<1> {
  static const int value = 0;
};

template<>
struct StaticLog2<0> {
};

constexpr unsigned static_log2(unsigned value) {
  return value > 1 ? static_log2(value / 2) + 1 : 0;
}


int main() {
  // std::cout << static_log2(5) << std::endl;
  // std::cout << static_log2(2) << std::endl;
  // std::cout << static_log2(0) << std::endl;
  std::cout << StaticLog2<5>::value << std::endl;
  std::cout << StaticLog2<2>::value << std::endl;
  // std::cout << StaticLog2<0>::value << std::endl;
  return 0;
}
