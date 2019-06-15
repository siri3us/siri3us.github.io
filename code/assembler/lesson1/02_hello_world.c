#include <unistd.h>

int main() {
  const char hello_str[] = "Hello, world!\n";
  write(1, hello_str, sizeof(hello_str) - 1);
  return 0;
}
