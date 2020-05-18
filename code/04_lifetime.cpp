#include <iostream>
#include <functional>
#include <vector>
#include "S.h"

// S()
// S(const S&)
// ~S()
// ~S()

const int& GetDataByRef() {
  const int i = 5;
  return i;
}

std::reference_wrapper<const int> GetDataByRefWrapper() {
  const int i = 5;
  return std::cref(i);
}

const char* GetConstCharString() {
  return "Hello World!";
}

#if __cplusplus==201703L
std::string_view GetStringView() {
  return "Hello World!";
}

std::string_view GetStringViewFromString() {
  const std::string msg = "Hello World!";
  return msg;
}

std::string_view GetStringViewFromCharArray() {
  const char msg[] = "Hello World!";
  return msg;
}
#endif

S GetSFromInitList() noexcept {
  return {};
}

S GetSFromLocal() noexcept {
  return S{};
}

struct A {
  const int& i;
};

struct B {
 public:
  B(int i) noexcept {
    puts("B(int)");
    ++allocations;
    ptr_ = new int(i);
  }

  // B(const B& other) noexcept {
  //   puts("B(const B&)");
  //   ptr_ = new int(*other.ptr_);
  // }
  //
  // B(B&& other) noexcept {
  //   puts("B(B&&)");
  //   ptr_ = other.ptr_;
  //   other.ptr_ = nullptr;
  // }

  ~B() noexcept {
    puts("~B()");
    delete ptr_;
  }

  static int allocations;

 private:
  int* ptr_{nullptr};
};

int B::allocations = 0;

int main() {
  {
    S s;

    {
      S s2{s};
    }

    {
      // It is not an object: no print from S methods
      [[maybe_unused]] S& s3{s};
    }
  }

  // ERROR: Both variants return reference to local variable
  // std::cout << GetDataByRef() << std::endl;
  std::cout << "BAD?: " << GetDataByRefWrapper() << std::endl;
  std::cout << "GOOD: " << GetConstCharString() << std::endl;
#if __cplusplus==201703L
  std::cout << "GOOD: " << GetStringView() << std::endl;
  std::cout << "BAD: " << GetStringViewFromString() << std::endl;
  std::cout << "BAD: " << GetStringViewFromCharArray() << std::endl;
#endif

  {
    // With C++17 and C++11/14 without "-fno-elide-constructors"
    // S(int)
    // S(S&&)
    // ~S()    # Temporary S{1} object destruction
    // ~S()    # Vector destruction
    std::cout << "\nvec.push_back(S{1})\n";
    std::vector<S> vec;
    vec.push_back(S{1});  // emplace_back is the same
  }

  {
    // With C++17 and C++11/14 without "-fno-elide-constructors"
    // S(int)
    // ~S()    # Vector destruction
    std::cout << "\nvec.emplace_back(1)\n";
    std::vector<S> vec;
    vec.emplace_back(1);
  }

  {
    // With C++17 and C++11/14 without "-fno-elide-constructors"
    // S()
    // ~S()    # Vector destruction
    std::cout << "\nvec.emplace_back()\n";
    std::vector<S> vec;
    vec.emplace_back();
  }

  {
    // With C++17 and C++11/14 ("-fno-elide-constructors" does not matter)
    // S()
    // ~S()
    std::cout << "\nconst auto& val = GetSFromInitList()\n";
    const auto& val = GetSFromInitList();
  }

  {
    // With C++17 and C++11/14 without "-fno-elide-constructors"
    // S()
    // ~S()
    //
    // With C++11/14 with "-fno-elide-constructors"
    // S()
    // S(S&&)
    // ~S()
    // ~S()
    std::cout << "\nconst auto& val = GetSFromLocal()\n";
    const auto& val = GetSFromLocal();
  }

  {
    // Lifetime extension rules apply recursively to member intializers
    const A& a = A{1};
    std::cout << "GOOD?: a.i = " << a.i << std::endl;
  }

  {
    std::vector<std::string> vec{"a", "b"};  // 1 allocation
  }

  {
    std::vector<std::string> vec{
      "Very very very very long string 1",
      "Very very very very long string 2"};
  }

  {
    std::vector<B> vec{1, 2};
    std::cout << "B::allocations = " << B::allocations << std::endl;
  }
}
