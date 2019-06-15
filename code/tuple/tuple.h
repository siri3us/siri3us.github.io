#include <type_traits>

template <typename F, typename T, bool Enough, int TotalArgs, int... N>
struct CallImpl {
  auto static Call(F&& f, T&& t) {
    return CallImpl<F, T, TotalArgs == 1 + sizeof...(N), TotalArgs, N..., sizeof...(N)>::Call(
        std::forward<F>(f), std::forward<T>(t));
  }
};

template <typename F, typename T, int TotalArgs, int... N>
struct CallImpl<F, T, true, TotalArgs, N...> {
  auto static Call(F&& f, T&& t) {
    return f(Get<N>(std::forward<T>(t))...);
  }
};

template <typename T = void>
struct TupleSize;

template <typename Head, typename... Args>
struct TupleSize<Tuple<Head, Args...>> {
  enum { value = 1 + TupleSize<Tuple<Args...>>::value };
};

template <>
struct TupleSize<Tuple<>> {
  enum { value = 0 };
};

template <typename F, typename T>
auto Call(F&& f, T&& t) {
  using TupleType = typename std::remove_const_t<typename std::remove_reference_t<T>>;
  return CallImpl<F, T, 0 == TupleSize<TupleType>::value, TupleSize<TupleType>::value>::Call(
      std::forward<F>(f), std::forward<T>(t));
}
