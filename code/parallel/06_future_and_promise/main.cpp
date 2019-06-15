#include <thread>
#include <future>
#include <iostream>
#include <chrono>

void Producer(std::promise<int>* promise) {
  std::this_thread::sleep_for(std::chrono::seconds{2});
  promise->set_value(100);
  std::this_thread::sleep_for(std::chrono::seconds{2});
}

int main() {
  std::promise<int> promise_value;
  std::future<int> future_value = promise_value.get_future();
  std::thread t(Producer, &promise_value);
  std::cout << future_value.get() << std::endl;
  t.join();
  return 0;
}
