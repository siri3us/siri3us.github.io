#include <iostream>

template <typename T1, typename T2, typename T3>
struct Triplet {
  /*
  Triplet(T1 first, T2 second, T3 third)
      : first(std::move(first)), second(std::move(second)), third(std::move(third)) {
  }
  */

  template <typename A1, typename A2, typename A3>
  Triplet(A1&& first, A2&& second, A3&& third)
      : first(std::forward<A1>(first))
      , second(std::forward<A2>(second))
      , third(std::forward<A3>(third)) {
  }

	T1 first;
	T2 second;
	T3 third;
};

template <typename A1, typename A2, typename A3>
Triplet(A1&&, A2&&, A3&&) -> Triplet<std::decay_t<A1>, std::decay_t<A2>, std::decay_t<A3>>;

int main() {
	// Triplet<int, double, unsigned> t{1, 1.2, 4u};
	Triplet t{1, 1.2, 4u};
  std::cout << t.first << ' ' << t.second << ' ' << t.third << std::endl;
	return 0;
}
