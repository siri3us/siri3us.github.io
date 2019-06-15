#include <gtest/gtest.h>
#include "cx_array_string.h"

TEST(CompileTimeArrayStringTestSuite, TestConstructors) {
  {
    constexpr static char str1[] = "Hello, world!";
    constexpr cx::array_string<cx::strlen(str1)> as1(str1);

    constexpr static char str2[] = "Goodbye, world!";
    constexpr cx::array_string<cx::strlen(str2)> as2(str2);

    constexpr auto as = as1 + as2;
    static_assert(as.size() == as1.size() + as2.size(), "");
    static_assert(as1[0] == 'H', "");
  }
  {
    constexpr static char str1[] = "Hel";
    constexpr cx::array_string<cx::strlen(str1)> as1(str1);

    constexpr static char str2[] = "lo";
    constexpr cx::array_string<cx::strlen(str2)> as2(str2);

    constexpr auto as = as1 + as2;
    static_assert(as[0] == 'H', "");
    static_assert(as[1] == 'e', "");
    static_assert(as[2] == 'l', "");
    static_assert(as[3] == 'l', "");
    static_assert(as[4] == 'o', "");
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
