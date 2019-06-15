#include <iostream>


class NonThrowingCopy {
  public:
    NonThrowingCopy() noexcept {}

    NonThrowingCopy(const NonThrowingCopy& source) noexcept
      : a(source.a) {
    }

  private:
    int a{0};
};

class ThrowingCopy {
  public:
    ThrowingCopy() noexcept {}

    ThrowingCopy(const ThrowingCopy& source) noexcept(false)
      : b(source.b) {
    }

  private:
    int b{1};
};


template <typename T>
T Copy(const T& src) noexcept(noexcept(T{src})) {
  return src;
}


int main() {
  NonThrowingCopy non_throwing;
  ThrowingCopy throwing;
  std::cout << std::boolalpha;
  std::cout << "Constructors exceptions:" << std::endl
            << "noexcept(NonThrowingCopy{}) = " << noexcept(NonThrowingCopy{}) << std::endl
            << "noexcept(ThrowingCopy{}) = " << noexcept(ThrowingCopy{}) << std::endl;
  std::cout << "\nCopy constructors exceptions:" << std::endl
            << "noexcept(NonThrowingCopy{non_throwing}) = " << noexcept(NonThrowingCopy{non_throwing}) << std::endl
            << "noexcept(ThrowingCopy{throwing}) = " << noexcept(ThrowingCopy{throwing}) << std::endl;
  std::cout << "\nCopy function exceptions:" << std::endl
            << "noexcept(Copy(non_throwing)) = " << noexcept(Copy(non_throwing)) << std::endl
            << "noexcept(Copy(throwing)) = " << noexcept(Copy(throwing)) << std::endl;
  return 0;
}
