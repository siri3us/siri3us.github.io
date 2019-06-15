#include <cstdio>

extern "C" {
	int sum(int a, int b);
}

int main() {
  printf("%d\n", sum(1, 2));
  return 0;
}
