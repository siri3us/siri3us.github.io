#include <iostream>
#include <cstdio>
#include <vector>
#include <type_traits>

#include "S.h"

int main() {
	std::cout << std::boolalpha;
	std::cout << "std::is_move_constructible<S>::value = "
            << std::is_move_constructible<S>::value << '\n';
	std::cout << "std::is_nothrow_move_constructible<S>::value = "
            << std::is_nothrow_move_constructible<S>::value << "\n\n";

	std::vector<S> vec;
  std::cout << "Creating S object:\n";
	S s{0};
	for (int i = 0; i < 5; ++ i) {
		std::cout << "\nAdding element " << i + 1 << '\n';
		vec.push_back(s);
    std::cout << "Vector capacity = " << vec.capacity() << '\n';
	}
  std::cout << std::endl;

	return 0;
};
