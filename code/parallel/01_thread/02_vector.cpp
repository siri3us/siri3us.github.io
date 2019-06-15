#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <exception>
#include <functional>

std::mutex gMutex;
std::vector<std::exception_ptr> gExceptions;

template <typename T>
class Vector {
  public:
    Vector() = default;

    Vector(std::initializer_list<T> init_list) {
      for (auto& value : init_list) {
        data_.push_back(value);
      }
    }

    const T& operator[] (int index) const {
      return data_[index];
    }

    T& operator[] (int index) {
      return data_[index];
    }

    const T& At(int index) const {
      try {
        return data_.at(index);
      } catch (...) {
        std::lock_guard guard(gMutex);
        gExceptions.push_back(std::current_exception());
        return data_.at(0);
      }
    }

    T& At(int index) {
      try {
        return data_.at(index);
      } catch (...) {
        std::lock_guard guard(gMutex);
        gExceptions.push_back(std::current_exception());
        return data_.at(0);
      }
    }

    template <typename Iter>
    size_t PushRange(Iter first, Iter end) {
      std::lock_guard guard(mutex_);
      size_t number_of_pushed = 0;
      for (; first != end; ++first) {
        data_.emplace_back(*first);
        ++number_of_pushed;
      }
      return number_of_pushed;
    }

    void PushBack(const T& value) {
      std::lock_guard guard(mutex_);
      data_.push_back(value);
    }

    void PushBack(T&& value) {
      std::lock_guard guard(mutex_);
      data_.push_back(std::move<T>(value));
    }

    template <typename ... Args>
    void EmplaceBack(Args&&... args) {
      std::lock_guard guard(mutex_);
      data_.emplace_back(std::forward<Args>(args)...);
    }

    void Dump() const {
      std::lock_guard guard(mutex_);
      std::stringstream ss;
      ss << "Vector state: ";
      for (auto& e: data_) {
        ss << e << ' ';
      }
      ss << '\n';
      std::cout << ss.str();
    }

  private:
    mutable std::mutex mutex_;
    std::vector<T> data_;
};


void AddElements(Vector<int>& vec, int value) {
  [[maybe_unused]] auto id = std::this_thread::get_id();
  std::stringstream ss;
  vec.PushBack(value);
  ss << "vec.At(4) = " << vec.At(4) << std::endl;
  std::cout << ss.str() << std::endl;
  vec.PushBack(value);
  vec.PushBack(value);
  vec.Dump();
}

int main() {
  Vector<int> vec;
  std::vector<std::thread> workers;
  std::cout << std::boolalpha;
  workers.emplace_back(AddElements, std::ref(vec), 1);
  workers.emplace_back(AddElements, std::ref(vec), 2);
  workers.emplace_back(AddElements, std::ref(vec), 3);

  auto WorkerStatusPrinter = [](const std::thread& worker) {
    std::stringstream ss;
    ss << std::boolalpha << "Thread with \"" << worker.get_id() << "\" is"
       << (worker.joinable() ? "" : " not") << " joinable: \n";
    std::cout << ss.str();
  };
  std::for_each(workers.begin(), workers.end(), WorkerStatusPrinter);

  std::vector<int> new_values = {4, 5, 6};
  vec.PushRange(new_values.begin(), new_values.end());
  vec.Dump();
  std::for_each(workers.begin(), workers.end(), std::mem_fn(&std::thread::join));
  std::for_each(workers.begin(), workers.end(), WorkerStatusPrinter);
  for (auto& e : gExceptions) {
    try {
      if (e != nullptr) {
        std::rethrow_exception(e);
      }
    } catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  }
  return 0;
}
