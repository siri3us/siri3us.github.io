#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "tuple.h"

TEST(TupleTestSuite, TestTupleCreation) {
  auto t = seq::Tuple<int, double, float>{1, 3.4, 5.1f};
  ASSERT_EQ(seq::Get<0>(t), 1);
  ASSERT_NEAR(seq::Get<1>(t), 3.4, 1e-8);
  ASSERT_NEAR(seq::Get<2>(t), 5.1f, 1e-8);
}

TEST(TupleTestSuite, TestOutput) {
  auto t = seq::Tuple<int, int, int>{1, 2, 3};
  std::stringstream ss;
  ss << t;
  EXPECT_EQ(ss.str(), "(1, 2, 3)");
}

TEST(TupleTestSuite, TestCall) {
  auto t = seq::Tuple<int, int, int>{1, 2, 3};
  auto sum = [] (int a, int b, int c) {
    return a + b + c;
  };
  ASSERT_EQ(seq::Call(sum, t), 6);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
