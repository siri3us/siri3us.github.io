#include <gtest/gtest.h>
#include <iostream>
#include <cstring>

#include "cx_array.h"
#include "cx_pair.h"
//#include "cx_vector.h"

template <std::size_t N>
constexpr cx::array<int, N> CreateRange() {
  cx::array<int, N> range;
  for (int i = 0; i < static_cast<int>(N); ++i) {
    range[i] = i;
  }
  return range;
}

TEST(ArrayCompileTimeTestSuite, TestConstructors) {
  {
    constexpr cx::array<int, 5> a;
    static_assert(a.size() == 5u, "");
    static_assert(a[0] == 0, "");
    static_assert(a[1] == 0, "");
    static_assert(a[2] == 0, "");
    static_assert(a[3] == 0, "");
    static_assert(a[4] == 0, "");
  }
  {
    constexpr cx::array<int, 5> a{1, 2, 3, 4, 5};
    static_assert(a.size() == 5u, "");
    static_assert(a[0] == 1, "");
    static_assert(a[1] == 2, "");
    static_assert(a[2] == 3, "");
    static_assert(a[3] == 4, "");
    static_assert(a[4] == 5, "");
  }
  {
    constexpr static int data[5] = {-5, -4, -3, -2, -1};
    constexpr cx::array<int, 5> a{data};
    static_assert(a.size() == 5u, "");
    static_assert(a[0] == -5, "");
    static_assert(a[1] == -4, "");
    static_assert(a[2] == -3, "");
    static_assert(a[3] == -2, "");
    static_assert(a[4] == -1, "");
  }
  {
    constexpr static char str[] = "Hello";
    constexpr cx::array<const char*, 5> a{str, str + 5};
    static_assert(a.size() == 5u, "");
    static_assert(a[0] == &str[0], "");
    static_assert(a[1] == &str[5], "");
    static_assert(a[2] == nullptr, "");
    static_assert(a[3] == nullptr, "");
    static_assert(a[4] == nullptr, "");
    static_assert(a.front() == &str[0], "");
    static_assert(a.back() == nullptr, "");
  }
  {
    constexpr cx::array<cx::array<int, 2>, 3> a = {{1, 2}, {3, 4}, {5, 6}};
    static_assert(a[0].size() == 2u, "");
    static_assert(a[1].size() == 2u, "");
    static_assert(a[2].size() == 2u, "");
    static_assert(a.size() == 3u, "");
    static_assert(a[0][0] == 1, "");
    static_assert(a[0][1] == 2, "");
    static_assert(a[1][0] == 3, "");
    static_assert(a[1][1] == 4, "");
    static_assert(a[2][0] == 5, "");
    static_assert(a[2][1] == 6, "");
  }
}

TEST(CompileTimeArrayTestSuite, Test) {
  {
    constexpr cx::array<int, 2> a{1, 2};
  }
}

TEST(RuntimeArrayTestSuite, Test) {
  {
    cx::array<int, 3> a{1, 2, 3};
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a.empty(), false);
    EXPECT_EQ(a.at(0), 1);
    EXPECT_EQ(a.at(1), 2);
    EXPECT_EQ(a.at(2), 3);
    EXPECT_THROW(a.at(3), std::range_error);
  }
  {
    cx::array<int, 4> a{1, 2, 3, 4};
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a[3], 4);
    EXPECT_NO_THROW(a[3]);
    EXPECT_THROW(a.at(4), std::runtime_error);
    EXPECT_THROW(a.at(5), std::runtime_error);
  }
}

TEST(ArrayTestSuite, CreateRange) {
  constexpr cx::array<int, 5> a = CreateRange<5>();
  static_assert(a.size() == 5u, "");
  static_assert(a[0] == 0, "");
  static_assert(a[1] == 1, "");
  static_assert(a[2] == 2, "");
  static_assert(a[3] == 3, "");
  static_assert(a[4] == 4, "");
  static_assert(a.front() == 0, "");
  static_assert(a.back() == 4, "");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
