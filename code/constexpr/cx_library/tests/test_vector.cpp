#include <gtest/gtest.h>
#include "cx_pair.h"
#include "cx_array.h"
#include "cx_vector.h"

constexpr auto TestVectorPushBack() {
  cx::vector<int, 15> vec;
  vec.push_back(15);
  vec.push_back(35);
  return vec;
}

TEST(VectorTestSuite, VectorConstructors) {
  {
    constexpr cx::vector<int, 10> vec;
    static_assert(vec.size() == 0u, "");
    static_assert(vec.empty(), "");
    static_assert(vec.capacity() == 10u, "");
  }
  {
    constexpr cx::vector<int> vec{0, 1, 2};
    static_assert(!vec.empty(), "");
    static_assert(vec.size() == 3u, "");
    static_assert(vec.capacity() == 10u, "");
    // Accessors
    static_assert(vec[0] == 0, "");
    static_assert(vec[1] == 1, "");
    static_assert(vec[2] == 2, "");
    static_assert(vec.front() == 0, "");
    static_assert(vec.back() == 2, "");
    // Iterators
    static_assert(*vec.begin() == 0u, "");
    static_assert(*vec.cbegin() == 0u, "");
    static_assert(vec.cend() - vec.cbegin() == 3u, "");
    static_assert(vec.end() - vec.begin() == 3u, "");
  }
  // Will not compile becuase of throw expression inside
  // constexpr cx::vector<int, 2> vec{0, 1, 2};
  {
    constexpr cx::vector<bool> vec{false, true, false};
    static_assert(!vec[0], "");
    static_assert(vec[1], "");
    static_assert(!vec[2], "");
  }
  {
    constexpr cx::vector<double> vec{0.5, 1.5, 2.0};
    static_assert(vec[0] == 0.5, "");
    static_assert(vec[1] == 1.5, "");
    static_assert(vec[2] == 2.0, "");
  }
}

TEST(VectorTestSuite, ComplexVectorConstructors) {
  {
    constexpr cx::vector<cx::pair<int, double>> vec{{1, 1.0}, {2, 2.0}, {3, 3.0}};
    static_assert(vec.size() == 3u, "");
    static_assert(vec.capacity() == 10u, "");
    static_assert(vec[0] == cx::make_pair(1, 1.0), "");
    static_assert(vec[1] == cx::make_pair(2, 2.0), "");
    static_assert(vec[2] == cx::make_pair(3, 3.0), "");
  }
  {
    constexpr cx::vector<cx::array<int, 2>, 4> vec{{1, 2}, {2, 3}};
    static_assert(vec.size() == 2u, "");
    static_assert(vec.capacity() == 4u, "");
    static_assert(vec[0] == cx::array<int, 2>{1, 2}, "");
    static_assert(vec[1] == cx::array<int, 2>{2, 3}, "");
  }
  {
    constexpr cx::vector<cx::vector<double>> vec{{1.0}, {1.0, 2.0}, {1.0, 2.0, 3.0}};
    static_assert(vec.size() == 3u, "");
    static_assert(vec.capacity() == 10u, "");
    static_assert(vec[0] == cx::vector<double>{1.0}, "");
    static_assert(vec[1] == cx::vector<double>{1.0, 2.0}, "");
    static_assert(vec[2] == cx::vector<double>{1.0, 2.0, 3.0}, "");
  }
}

TEST(CompileTimeVectorTestSuite, TestAccessOperators) {
  constexpr cx::vector<double> v = {1.0, 2.0, 3.0};
  static_assert(v[0] == 1.0, "");
  static_assert(v[1] == 2.0, "");
  static_assert(v[2] == 3.0, "");
  static_assert(v.size() == 3u, "");
  EXPECT_THROW(v.at(3), std::range_error);
}

TEST(VectorTestSuite, TestPushBack) {
  constexpr auto vec = TestVectorPushBack();
  static_assert(vec.size() == 2u, "");
  static_assert(!vec.empty(), "");
  static_assert(vec.capacity() == 15u, "");
  static_assert(vec[0] == 15, "");
  static_assert(vec[1] == 35, "");
  static_assert(vec.front() == 15, "");
  static_assert(vec.back() == 35, "");
}

TEST(VectorTestSuite, TestEqualityOperators) {
  constexpr cx::vector<int> v1{1, 2, 3, 4, 5};
  constexpr cx::vector<int> v2{1, 2, 3, 4, 5};
  constexpr cx::vector<int> v3{1, 2, 3, 4};
  static_assert(v1 == v2, "");
  static_assert(v1 != v3, "");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
