#include <gtest/gtest.h>
#include "tuple.h"

double FindSum(double a, double b, double c) {
  return a + b + c;
}

TEST(TestSum, TestTupleSum) {
  auto t = Tuple<int, int, int>{1, 2, 3};
  EXPECT_EQ(Call(FindSum, t), 6);
  std::cout << Call(FindSum, t) << std::endl;
}

TEST(TestTuple, TestTupleSize) {
  auto t = Tuple<int, double, int>{12, 2.34, 89};
  EXPECT_EQ(TupleSize<decltype(t)>::value, 3);
  auto t2 = Tuple<int, double, int, const char*>{12, 2.34, 89, "sdfd"};
  EXPECT_EQ(TupleSize<decltype(t2)>::value, 4);
  EXPECT_EQ(TupleSize<Tuple<>>::value, 0);
}

TEST(TestTuple, TestConstruction) {
  auto t = Tuple<int, double, int>{12, 2.34, 89};
  EXPECT_EQ(t.head_, 12);
  EXPECT_FLOAT_EQ(t.tail_.head_, 2.34);
  EXPECT_EQ(t.tail_.tail_.head_, 89);
  std::cout << t.head_ << ' ' << t.tail_.head_ << ' ' << t.tail_.tail_.head_ << std::endl;
}

TEST(TestTuple, TestGet) {
  auto t = Tuple<int, double, int>{12, 2.34, 89};
  EXPECT_EQ(Get<0>(t), 12);
  EXPECT_FLOAT_EQ(Get<1>(t), 2.34);
  EXPECT_EQ(Get<2>(t), 89);
  std::cout << Get<0>(t) << ' ' << Get<1>(t) << ' ' << Get<2>(t) << std::endl;
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
