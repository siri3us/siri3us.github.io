#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

template <typename T>
void PrintClassTraits() {
  std::cout << std::string(50, '*') << std::endl;
  std::cout << "PrintClassTraits" << std::endl;
  std::cout << std::boolalpha;
  std::cout << "std::is_default_constructable_v<S> = " << std::is_default_constructible_v<T> << '\n';
  std::cout << "std::is_copy_constructable_v<S>    = " << std::is_copy_constructible_v<T> << '\n';
  std::cout << "std::is_copy_assignable_v<S>       = " << std::is_copy_assignable_v<T> << '\n';
  std::cout << "std::is_move_constructable_v<S>    = " << std::is_move_constructible_v<T> << '\n';
  std::cout << "std::is_move_assignable_v<S>       = " << std::is_move_assignable_v<T> << '\n';

  std::cout << "\nNothrow methods:\n";
  std::cout << "std::is_nothrow_default_constructable_v<S> = " << std::is_nothrow_default_constructible_v<T> << '\n';
  std::cout << "std::is_nothrow_copy_constructable_v<S>    = " << std::is_nothrow_copy_constructible_v<T> << '\n';
  std::cout << "std::is_nothrow_copy_assignable_v<S>       = " << std::is_nothrow_copy_assignable_v<T> << '\n';
  std::cout << "std::is_nothrow_move_constructable_v<S>    = " << std::is_nothrow_move_constructible_v<T> << '\n';
  std::cout << "std::is_nothrow_move_assignable_v<S>       = " << std::is_nothrow_move_assignable_v<T> << '\n';
  std::cout << "std::is_nothrow_destructible_v<S>          = " << std::is_nothrow_destructible_v<T> << '\n';

  T s1{5};
  T s2{10};
  std::cout << "\nNoexcept:\n";
  std::cout << "noexcept(S(int))                 = " << noexcept(T{1}) << '\n';
  std::cout << "noexcept(S(const S&))            = " << noexcept(T{s1}) << '\n';
  std::cout << "noexcept(S& operator=(const S&)) = " << noexcept(s2 = s1) << '\n';
  std::cout << "noexcept(S(S&&))                 = " << noexcept(T{std::move(s2)}) << '\n';
  std::cout << "noexcept(S& operator=(S&&))      = " << noexcept(s1 = std::move(s2)) << '\n';
  std::cout << "noexcept(~S())                   = " << noexcept(s1.~T()) << '\n';
  std::cout << std::string(50, '*') << std::endl;
}

template <typename T>
std::vector<T> TestVectorPushBack(const T& value, int number) {
  std::cout << std::string(50, '*') << std::endl;
  std::cout << "TestVectorPushBack\n";
  std::vector<T> values;
  for (int i = 0; i < number; ++i) {
    values.push_back(value);
  }
  std::cout << std::string(50, '*') << std::endl;
  return values;
}
