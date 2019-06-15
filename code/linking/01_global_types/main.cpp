#include <cstdio>
// Initialized global variable (promise to symbols.cpp)
int z_global = 4;

static int y_global_init = 5;

extern int x_global_init;

int fn_a(int x, int y) {
  return x + y;
}

int fn_c(int x_local);

int main() {
  const char *message = "Hello, world!";
  int x_local = fn_a(6, 7);
  int result = fn_c(x_local + y_global_init);
  printf("Result of f_c(%d) = %d\n", x_local, result);
  return 0;
}
