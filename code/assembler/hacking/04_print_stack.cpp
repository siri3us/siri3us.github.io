#include <stdio.h>

void DefineNumbers() {
  int a = 1;
  int b = 2;
  int c = 3;
  (void) a;
  (void) b;
  (void) c;
}

void Print() {
  int a;
  int b;
  int c;
  printf("%d %d %d\n", a, b, c);
}

int main() {
	DefineNumbers();
	Print();
	return 0;
}
