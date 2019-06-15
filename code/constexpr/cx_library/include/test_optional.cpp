#include <gtest/gtest.h>
#include "cx_optional.h"

TEST(OptionalTestSuite, TestContructors) {
  constexpr cx::optional<double> o{1.5};
  static_assert(*o == 1.5, "");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
