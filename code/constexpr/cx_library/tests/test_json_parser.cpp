#include <gtest/gtest.h>
#include "cx_json_parser.h"

using cx::operator""_ss;

TEST(JsonParserTestSuite, TestLiterals) {
  constexpr auto str = "Hello"_ss;
  static_assert(str.Size() == 5u, "");
  static_assert(str == "Hello", "");
}

TEST(JsonParserTestSuite, TestParseUnknown) {
  {
    constexpr auto result = cx::json::ParseUnknown<5>(0, R"("true")");
    static_assert(result.first == 6, "");
    static_assert(result.second.GetType() == cx::JsonType::Boolean, "");
    static_assert(static_cast<bool>(result.second) == true, "");
  }

  {
    constexpr auto result = cx::json::ParseUnknown<5>(0, R"("false")");
    static_assert(result.first == 7, "");
    static_assert(result.second.GetType() == cx::JsonType::Boolean, "");
    static_assert(static_cast<bool>(result.second) == false, "");
  }

  {
    constexpr auto result = cx::json::ParseUnknown<5>(0, R"("null")");
    static_assert(result.first == 6, "");
    static_assert(result.second.GetType() == cx::JsonType::Null, "");
  }

  {
    constexpr auto result = cx::json::ParseUnknown<5>(0, R"("Hello, world!")");
    static_assert(result.first == 15, "");
    static_assert(result.second.GetType() == cx::JsonType::String, "");
    static_assert(static_cast<cx::StaticString>(result.second) == "Hello, world!", "");
  }

  {
    constexpr auto result = cx::json::ParseUnknown<5>(0, R"("Hello")");
    static_assert(result.first == 7, "");
    static_assert(result.second.GetType() == cx::JsonType::String, "");
    static_assert(static_cast<cx::StaticString>(result.second) == "Hello", "");
  }
}

TEST(JsonParserTestSuite, TestParseJsonObject) {
  {
    constexpr static const char* str = "{Hello, world!}";
    constexpr auto json_value = cx::json::ParseJsonObject<5>(0, str);
  }
  {
    constexpr static const char* str = "{Hello, {{1: 2, 3: 3}}world!}";
    constexpr auto json_value = cx::json::ParseJsonObject<5>(0, str);
  }
  {
    constexpr static const char* str = "Hello, world!";
    EXPECT_THROW(cx::json::ParseJsonObject<5>(0, str), std::runtime_error);
  }
}

TEST(JsonParserTestSuite, TestParseJsonArray) {
  {
    constexpr static const char* str = R"(["Hello"])";
    // constexpr static const char* str = R"(  ["Hello", "world", "true", "false", "null"]\t\t)";
    constexpr auto result = cx::json::ParseJsonArray<5>(0, str);
    constexpr auto json = result.second;
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
