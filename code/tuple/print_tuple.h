#include <tuple>
#include <iostream>
#include <utility>
#include <array>

template <typename... Args, int... Indices>
void PrintTupleImpl(const std::tuple<Args...>& t, std::integer_sequence<int, Indices...>) {
  ((std::cout << (Indices == 0 ? "" : ", ") << std::get<Indices>(t)), ...);
}

template <typename... Args>
void PrintTuple(std::tuple<Args...>& t) {
  std::cout << "(";
  PrintTupleImpl(t, std::make_integer_sequence<int, sizeof...(Args)>());
  std::cout << ")" << std::endl;
}


template <typename T, std::size_t N, std::size_t... Indices>
auto Array2TupleImpl(const std::array<T, N>& a, std::integer_sequence<std::size_t, Indices...>) {
  return std::make_tuple(a[Indices]...);
}

template <typename T, std::size_t N>
auto Array2Tuple(const std::array<T, N>& a) {
  return Array2TupleImpl(a, std::make_integer_sequence<std::size_t, N>());
}
