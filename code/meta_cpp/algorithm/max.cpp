#include <iostream>
#include <type_traits>

template <typename T>
T max_by_value(T a, T b) {
  return a > b ? a : b;
}

template <typename T>
T& max_by_reference(T& a, T& b) {
  return a > b ? a : b;
}

template <typename T>
auto max(T a, T b) -> decltype(b < a ? a : b) {
  // std::cout << "&max::a = " << &a << std::endl;
  // std::cout << "&max::b = " << &b << std::endl;
  return b < a ? a : b;
}

// template <typename T1, typename T2>
// auto max(T1 a, T2 b) -> decltype(b < a ? a : b) {
//   std::cout << "&max::a = " << &a << std::endl;
//   std::cout << "&max::b = " << &b << std::endl;
//   return b < a ? a : b;
// }

// template <typename T1, typename T2>
// auto max(T1 a, T2 b) -> std::decay_t<decltype(b < a ? a : b)> {
//   // std::cout << "&max::a = " << &a << std::endl;
//   // std::cout << "&max::b = " << &b << std::endl;
//   return b < a ? a : b;
// }


int main() {
  int a = 1;
  const int b = 2;
  [[maybe_unused]] int& ref_a = a;
  [[maybe_unused]] const int& ref_b = b;

  decltype(b < a ? a : b) m = b < a ? a : b;
  std::cout << "&a = " << &a << std::endl;
  std::cout << "&b = " << &b << std::endl;
  std::cout << "&m = " << &m << std::endl;

  int c[4] = {};
  std::cout << max_by_value(a, b) << std::endl;
  std::cout << max_by_value(&a, c) << std::endl;
  std::cout << "********************" << std::endl;
  auto&& r1 = max(a, b);
  std::cout << "&r1 = " << &r1 << std::endl;
  std::cout << "********************" << std::endl;
  auto&& r2 = max(a, b);
  std::cout << "&r2 = " << &r2 << std::endl;
  std::cout << "********************" << std::endl;
  [[maybe_unused]] auto r3 = max(1.0 * a, b);
  std::cout << "&r3 = " << &r3 << std::endl;
  std::cout << "********************" << std::endl;
  return 0;
}
