#include <cstdio>

int main() {
	int a = 5;
	auto&& b = a++;
	auto&& c = ++a;
	++a;
	printf("%d %d %d\n", a, b, c);
	return 0;
}
