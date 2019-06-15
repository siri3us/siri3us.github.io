#include <gtest/gtest.h>
#include "cx_static_string.h"
#include "cx_basic_string.h"

TEST(BasicStringTestSuite, TestConstructors) {
  {
    constexpr char hello_string[] = "Hello, world!";
    constexpr auto str = cx::BasicString<char, 14>(hello_string);
    static_assert(str[0] == 'H', "");
    static_assert(str[12] == '!', "");
    static_assert(str[13] == '\0', "");
  }

  { constexpr auto hello_string = cx::StaticString("Hello, world!"); }

  {
    constexpr static char s[5] = "abcd";
    constexpr cx::BasicString<char, 5> bs{s};
  }

  {
    constexpr static char s[4] = {'a', 'b', 'c', 'd'};
    constexpr cx::BasicString<char, 5> bs{s};
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
