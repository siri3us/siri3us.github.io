#include <iostream>
#include <cstdio>
#include <vector>
#include <type_traits>

struct S {
	public:
		S(int i) : i_{i} { puts("S(int)"); }
		~S() { puts("~S()"); }
		S(const S& source) { puts("S(const S&)"); }
		S& operator=(const S& rhs)  { puts("S& operator=(const S&)"); return *this; }
#ifdef NOEXCEPT
		S(S&& source) noexcept { puts("S(S&&)"); }
		S& operator=(S&& rhs) noexcept { puts("S& operator=(S&&)"); return *this; }
#else
    S(S&& source) { puts("S(S&&)"); }
		S& operator=(S&& rhs) { puts("S& operator=(S&&)"); return *this; }
#endif
  private:
    int i_;
};

int main() {
	std::vector<S> vec;
	std::cout << std::boolalpha;
	std::cout << "std::is_move_constructible<S>::value = " << std::is_move_constructible<S>::value << std::endl;
	std::cout << "std::is_nothrow_move_constructible<S>::value = " << std::is_nothrow_move_constructible<S>::value << std::endl;
	S s{0};
	for (int i = 0; i < 5; ++ i) {
		std::cout << "Adding element " << i << std::endl;
		vec.push_back(s);
	}
	return 0;
};
