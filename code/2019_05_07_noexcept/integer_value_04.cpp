#include <iostream>

class IntegerValue {
  public:
    explicit IntegerValue(int value = 0) noexcept : value_(value) {
    }

    int GetValue() const noexcept {
      return value_;
    }

  private:
    int value_;
};

IntegerValue operator+(const IntegerValue& lhs, const IntegerValue& rhs) noexcept {
  return IntegerValue{lhs.GetValue() + rhs.GetValue()};
}

[[maybe_unused]] static void PrintNoexcept() {
  IntegerValue var;
  std::cout << std::boolalpha;
  std::cout << "noexcept(IntegerValue::IntegerValue()) = " << noexcept(IntegerValue{}) << std::endl;
  std::cout << "noexcept(IntegerValue::GetValue()) = " << noexcept(var.GetValue()) << std::endl;
  std::cout << "noexcept(operator+) = " << noexcept(var + var) << std::endl;
  std::cout << "noexcept(IntegerValue::~IntegerValue()) = " << noexcept(var.~IntegerValue()) << std::endl;
}

int main(int argc, char *argv[]) {
  int result = 0;
  try {
    IntegerValue var1{5};
    IntegerValue var2{100};
    result = (var1.GetValue() + var2.GetValue() > 0) ? 0 : -1;
  } catch (...) {
    result = -1;
    std::cerr << "Error happended!" << std::endl;
  }
  return result;
}
