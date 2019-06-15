#include <iostream>
#include <unistd.h>

int main() {
    std::cout << 1; // << std::endl;
    // std::cout << 1 << std::endl;
    fork();
    exit(0);
}
