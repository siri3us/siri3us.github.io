#include <algorithm>

namespace seq {

template <typename T, T... Ns>
struct Sequence {
  using ValueType = T;
  static constexpr std::size_t Size() {
    return sizeof...(Ns);
  }
};

namespace {

template <std::size_t...>
struct IndexSequenceImpl;

template <std::size_t N, std::size_t I, std::size_t... Ns>
struct IndexSequenceImpl<N, I, Ns...> {
  using Type = typename IndexSequenceImpl<N, I - 1, I, Ns...>::Type;
};

template <std::size_t N, std::size_t... Ns>
struct IndexSequenceImpl<N, 0, Ns...> {
  using Type = Sequence<std::size_t, 0, Ns...>;
};

template <>
struct IndexSequenceImpl<0> {
  using Type = Sequence<std::size_t>;
};

template <std::size_t N>
struct IndexSequenceImpl<N> {
  using Type = typename IndexSequenceImpl<N, N - 1>::Type;
};

}  // anonymous namespace

template <std::size_t... Ns>
using IndexSequence = Sequence<std::size_t, Ns...>;

template <std::size_t N>
constexpr auto CreateIndexSequence() {
  return typename IndexSequenceImpl<N>::Type{};
}

// InSequence
template <typename T, T value, typename U>
struct InSequence;

template <typename T, T I, typename U, U... Ns>
struct InSequence<T, I, Sequence<U, Ns...>> {
  constexpr static bool value = false;
};

template <typename T, T I, T F, T... Ns>
struct InSequence<T, I, Sequence<T, F, Ns...>> {
  constexpr static bool value = InSequence<T, I, Sequence<T, Ns...>>::value;
};

template <typename T, T I, T... Ns>
struct InSequence<T, I, Sequence<T, I, Ns...>> {
  constexpr static bool value = true;
};

template <typename T, T I>
struct InSequence<T, I, Sequence<T>> {
  constexpr static bool value = false;
};

// MaxSequence
template <typename S>
struct MaxSequence {};

template <typename T, T I, T... Ns>
struct MaxSequence<Sequence<T, I, Ns...>> {
  constexpr static T value = std::max<T>(I, MaxSequence<Sequence<T, Ns...>>::value);
};

template <typename T, T I>
struct MaxSequence<Sequence<T, I>> {
  constexpr static T value = I;
};

// MaxSequence
template <typename S>
struct MinSequence {};

template <typename T, T I, T... Ns>
struct MinSequence<Sequence<T, I, Ns...>> {
  constexpr static T value = std::min<T>(I, MinSequence<Sequence<T, Ns...>>::value);
};

template <typename T, T I>
struct MinSequence<Sequence<T, I>> {
  constexpr static T value = I;
};

template <typename T, T value, typename S>
constexpr static bool in_sequence_v = InSequence<T, value, S>::value;

template <typename S>
constexpr static std::size_t sequence_size_v = S::Size();

template <typename S>
constexpr static typename S::ValueType max_sequence_v = MaxSequence<S>::value;

template <typename S>
constexpr static typename S::ValueType min_sequence_v = MinSequence<S>::value;

}  // namespace seq
