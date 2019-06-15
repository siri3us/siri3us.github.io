#include <gtest/gtest.h>
#include "cx_array.h"
#include "cx_static_string.h"

TEST(StaticStringTestSuite, TestConstructors) {
  {
    constexpr auto str = cx::StaticString("abc", 3);
    static_assert(str.Size() == 3, "");
    static_assert(str[0] == 'a', "");
    static_assert(str[1] == 'b', "");
    static_assert(str[2] == 'c', "");
  }
  {
    constexpr auto str = cx::StaticString("abc");
    static_assert(str.Size() == 3, "");
    static_assert(str[0] == 'a', "");
    static_assert(str[1] == 'b', "");
    static_assert(str[2] == 'c', "");
  }
  {
    constexpr static char data[] = "abc";
    constexpr auto str = cx::StaticString(data);
    static_assert(str.Size() == 3, "");
    static_assert(str[0] == 'a', "");
    static_assert(str[1] == 'b', "");
    static_assert(str[2] == 'c', "");
  }
  {
    constexpr static cx::Array<char, 4> data{'a', 'b', 'c', '\0'};
    constexpr auto str = cx::StaticString(data);
    static_assert(str.Size() == 3, "");
    static_assert(str[0] == 'a', "");
    static_assert(str[1] == 'b', "");
    static_assert(str[2] == 'c', "");
  }
}

TEST(StaticStringTestSuite, TestGetSubString) {
  {
    constexpr auto str = cx::StaticString("abc def");
    constexpr auto str1 = str.GetSubString(4);
    static_assert(str1 == "def", "");
    constexpr auto str2 = str.GetSubString(1, 2);
    static_assert(str2 == "bc", "");
    constexpr auto str3 = str.GetSubString(2, 5);
    static_assert(str3 == "c def", "");
  }
}

TEST(StaticStringTestSuite, TestOperators) {
  {
    constexpr cx::StaticString v{"hello"};
    static_assert(v == "hello", "");
    static_assert("hello" == v, "");
    static_assert(v != "helo", "");
    static_assert("helo" != v, "");
    static_assert(v < "www", "");
    static_assert("www" > v, "");
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
