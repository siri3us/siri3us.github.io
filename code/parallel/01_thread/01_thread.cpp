#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <exception>

void Function1() {
  std::stringstream ss;
  ss << "Thread with id " << std::this_thread::get_id() << " calling function 1" << std::endl;
  std::cout << ss.str();
}

void Function2() {
#ifdef THROW
  throw std::runtime_error("Something wrong in the thread");
#else
  std::stringstream ss;
  ss << "Thread with id " << std::this_thread::get_id() << " calling function 2" << std::endl;
  std::cout << ss.str();
#endif
}

void Function3() {
  std::chrono::duration<double> duration{5};
  std::this_thread::sleep_for(duration);
  std::stringstream ss;
  ss << "Thread with id " << std::this_thread::get_id() << " calling function 3" << std::endl;
  std::cout << ss.str();
}

int main() {
  try {
  std::vector<std::thread> threads;
  std::cout << "Approximate number of workers: " << std::thread::hardware_concurrency() << std::endl;
  threads.emplace_back(Function1);
  threads.emplace_back(Function2);
  threads.emplace_back(Function3);
  for (auto& t : threads) {
    t.join();
  }
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}
