#include <gtest/gtest.h>
#include "cx_pair.h"
#include "cx_array.h"

constexpr void TestPairCreation() {
  constexpr auto p = cx::pair<int, double>{5, 1.5};
  constexpr auto s = static_cast<double>(p.first) + p.second;
  static_assert(p.first == 5, "First value must be 5");
  static_assert(p.second == 1.5, "Second value must be 1.5");
  static_assert(s == 6.5, "Sum must be equal 6.5");

  constexpr auto p2 = cx::make_pair("abc", 45);
  static_assert(p2.first[0] == 'a', "First value must be \"abc\"");
  static_assert(p2.first[1] == 'b', "First value must be \"abc\"");
  static_assert(p2.first[2] == 'c', "First value must be \"abc\"");
  static_assert(p2.second == 45, "Second value must be 45");
}

constexpr auto CreatePairOfArray() {
  auto p = cx::pair<cx::array<int, 5>, cx::array<double, 10>>{};
  p.first[0] = 0;
  p.first[1] = 1;
  p.first[2] = 2;

  p.second[0] = 2.0;
  p.second[1] = 1.0;
  p.second[2] = 0.0;

  return p;
}

constexpr void TestPairOfArray() {
  constexpr auto p = CreatePairOfArray();
  static_assert(p.first[0] == 0, "");
  static_assert(p.first[1] == 1, "");
  static_assert(p.first[2] == 2, "");
  static_assert(p.second[0] == 2.0, "");
  static_assert(p.second[1] == 1.0, "");
  static_assert(p.second[2] == 0.0, "");
}

TEST(pairTestSuite, pairTestSuite) {
  TestPairCreation();
  TestPairOfArray();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
