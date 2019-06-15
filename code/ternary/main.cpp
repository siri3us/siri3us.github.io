#include <iostream>
#include <cstdio>
#include <vector>
#include <random>

void PrintAsString(bool value) {
  std::cout << "Bool passed: " << value << std::endl;
}

void PrintAsString(const char* value) {
  std::cout << "Const char* passed: " << value << std::endl;
}

void PrintAsString(const std::string& value) { 
  std::cout << "Const string passed: " << value << std::endl;
}

int main() {
	std::cout << std::boolalpha;
	auto x = (std::rand() % 2) ? "Hello" : true;
	auto y = (std::rand() % 2) ? "Hello" : 1;
  auto z = (std::rand() % 2) ? "Hello" : std::string("world");
  std::cout << x << std::endl;
  std::cout << y << std::endl;
  std::cout << z << std::endl;
  PrintAsString(true);
  PrintAsString("const char*");
  PrintAsString(std::string{"string"});
  return 0;
}
