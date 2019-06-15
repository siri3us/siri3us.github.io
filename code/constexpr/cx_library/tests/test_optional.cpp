#include <gtest/gtest.h>
#include "cx_optional.h"

TEST(OptionalTestSuite, TestContructors) {
  {
    constexpr cx::optional<int> o;
    static_assert(!static_cast<bool>(o), "");
  }
  {
    constexpr cx::optional<double> o{1.5};
    static_assert(*o == 1.5, "");
  }
}

TEST(OptionalTestSuite, TestRunTime) {
  {
    cx::optional<int> o;
    EXPECT_FALSE(static_cast<bool>(o));
    o = 10;
    EXPECT_TRUE(static_cast<bool>(o));
    EXPECT_EQ(*o, 10);
    *o = 5;
    EXPECT_EQ(*o, 5);
    *o += 2;
    EXPECT_EQ(*o, 7);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
