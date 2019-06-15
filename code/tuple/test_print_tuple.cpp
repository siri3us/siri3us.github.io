#include <gtest/gtest.h>
#include "print_tuple.h"


TEST(PrintTupleTestSuite, PrintTuple) {
  auto t = std::make_tuple(1, 2, 3, 4, "abc");
  PrintTuple(t);
}

TEST(Array2TupleTestSuite, Array2Tuple) {
  std::array<int, 4> a = {44, 33, 22, 11};
  auto t = Array2Tuple(a);
  PrintTuple(t);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
