#include <iostream>
#include "sequence.h"

namespace seq {

template <typename... Args>
struct Tuple;

template <typename Head, typename... Tail>
struct Tuple<Head, Tail...> : Tuple<Tail...> {
  constexpr Tuple(Head head, Tail... tail) : head_(head), Tuple<Tail...>(tail...) {
  }

  using HeadType = Head;
  using TailType = Tuple<Tail...>;

  static constexpr std::size_t Size() {
    return sizeof...(Tail) + 1u;
  }

  HeadType head_;
  TailType& tail_ = static_cast<TailType&>(*this);
};

template <>
struct Tuple<> {
  static constexpr std::size_t Size() {
    return 0u;
  }
};

namespace {

template <std::size_t I, typename... T>
struct Getter;

template <std::size_t I, typename... Args>
struct Getter<I, Tuple<Args...>> {
  constexpr static auto Get(const Tuple<Args...>& t) {
    return Getter<I - 1, typename Tuple<Args...>::TailType>::Get(t.tail_);
  }
};

template <typename... Args>
struct Getter<0, Tuple<Args...>> {
  constexpr static auto Get(const Tuple<Args...>& t) {
    return t.head_;
  }
};

template <std::size_t I>
struct Getter<I, Tuple<>> {};

}  // anonymous namespace

template <std::size_t I, typename... Args>
constexpr static auto Get(const Tuple<Args...>& t) {
  return Getter<I, Tuple<Args...>>::Get(t);
}

namespace {

template <typename... Args, std::size_t... Indices>
void PrintTupleImpl(std::ostream& os, const Tuple<Args...>& t, seq::IndexSequence<Indices...>) {
  ((os << (Indices == 0 ? "" : ", ") << Get<Indices>(t)), ...);
}

}  // anonymous namespace

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const Tuple<Args...>& t) {
  os << '(';
  PrintTupleImpl(os, t, seq::CreateIndexSequence<sizeof...(Args)>());
  os << ')';
  return os;
}

namespace {

template <typename Func, typename... Args, std::size_t... Indices>
auto CallImpl(Func&& func, const Tuple<Args...>& t, IndexSequence<Indices...>) {
  return func(Get<Indices>(t)...);
}

}  // anonymous namespace

template <typename Func, typename... Args>
auto Call(Func&& func, const Tuple<Args...>& t) {
  return CallImpl(std::forward<Func>(func), t, seq::CreateIndexSequence<sizeof...(Args)>());
}

}  // namespace seq
