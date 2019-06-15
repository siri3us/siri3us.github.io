#include <iostream>
#include <thread>
#include <vector>


int main() {
  auto l1 = [] {
    static int value;
    if (value % 2) {
      value += 1;
    } else {
      value += 2;
    }
    return ++value;
  };

  auto worker = [l1]() {
    for (int i = 0; i < 1000; ++i) {
      l1();
    }
  };

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i) {
    threads.push_back(std::thread{worker});
  }
  worker();

  for (auto& t : threads) {
    t.join();
  }
  std::cout << l1() << std::endl;
  return 0;
}
