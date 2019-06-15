#include <gtest/gtest.h>
#include <iostream>

#include "cx_json_value.h"

constexpr auto CreateNullJsonValue() {
  constexpr cx::JsonValue<5> j;
  j.AssertType(cx::JsonType::Null);
  j.AssertNull();
  return j;
}

constexpr auto CreateBooleanJsonValue(bool value) {
  cx::JsonValue<5> j{value};
  j.AssertType(cx::JsonType::Boolean);
  j.AssertBoolean();
  return j;
}

constexpr auto CreateNumberJsonValue(double value) {
  cx::JsonValue<5> j{value};
  j.AssertType(cx::JsonType::Number);
  j.AssertNumber();
  return j;
}

constexpr auto CreateStringJsonValue(const cx::StaticString& value) {
  cx::JsonValue<5> j{value};
  j.AssertType(cx::JsonType::String);
  j.AssertString();
  return j;
}

TEST(JsonValueTestSuite, TestConstructors) {
  {
    constexpr auto j = CreateNullJsonValue();
    static_assert(j.GetType() == cx::JsonType::Null, "");
    EXPECT_THROW(j.AssertType(cx::JsonType::Number), std::runtime_error);
  }

  {
    constexpr auto j1 = CreateBooleanJsonValue(false);
    static_assert(j1.GetType() == cx::JsonType::Boolean, "");
    static_assert(static_cast<const bool&>(j1) == false, "");

    constexpr auto j2 = CreateBooleanJsonValue(true);
    static_assert(j2.GetType() == cx::JsonType::Boolean, "");
    static_assert(static_cast<const bool&>(j2) == true, "");
  }

  {
    constexpr auto j1 = CreateNumberJsonValue(1.5);
    static_assert(j1.GetType() == cx::JsonType::Number, "");
    static_assert(static_cast<const double&>(j1) == 1.5, "");

    constexpr auto j2 = CreateNumberJsonValue(1.5);
    static_assert(j2.GetType() == cx::JsonType::Number, "");
    static_assert(static_cast<const double&>(j2) == 1.5, "");
  }

  {
    constexpr auto j1 = CreateStringJsonValue("abcd efg");
    static_assert(j1.GetType() == cx::JsonType::String, "");
    static_assert(static_cast<const cx::StaticString&>(j1) == "abcd efg", "");

    constexpr auto j2 = CreateStringJsonValue("!!!");
    static_assert(j2.GetType() == cx::JsonType::String, "");
    static_assert(static_cast<const cx::StaticString&>(j2) == "!!!", "");
  }
}

TEST(JsonValueTestSuite, RunTimeConstructors) {
  {
    cx::JsonValue<5> j;
    EXPECT_NO_THROW(j.AssertNull());
    EXPECT_THROW(j.AssertBoolean(), std::runtime_error);
    EXPECT_THROW(j.AssertNumber(), std::runtime_error);
    EXPECT_THROW(j.AssertString(), std::runtime_error);

    j = 10.;
    EXPECT_NO_THROW(j.AssertNumber());
    EXPECT_THROW(j.AssertNull(), std::runtime_error);
    EXPECT_THROW(j.AssertBoolean(), std::runtime_error);
    EXPECT_THROW(j.AssertString(), std::runtime_error);

    j = false;
    EXPECT_NO_THROW(j.AssertBoolean());
    EXPECT_THROW(j.AssertNull(), std::runtime_error);
    EXPECT_THROW(j.AssertNumber(), std::runtime_error);
    EXPECT_THROW(j.AssertString(), std::runtime_error);

    j = "abc";
    EXPECT_NO_THROW(j.AssertString());
    EXPECT_THROW(j.AssertNull(), std::runtime_error);
    EXPECT_THROW(j.AssertBoolean(), std::runtime_error);
    EXPECT_THROW(j.AssertNumber(), std::runtime_error);
  }
}

constexpr auto ChangeJsonValue(bool value) {
  auto j = CreateNullJsonValue();
  j.ToBoolean() = value;
  return j;
}

constexpr auto ChangeJsonValue(double value) {
  auto j = CreateNullJsonValue();
  j.ToNumber() = value;
  return j;
}

constexpr auto ChangeJsonValue(const cx::StaticString value) {
  auto j = CreateNullJsonValue();
  j.ToString() = value;
  return j;
}

TEST(JsonValueTestSuite, TestToType) {
  {
    constexpr auto j = ChangeJsonValue(true);
    static_assert(j.ToBoolean() == true, "");
    static_assert(static_cast<const bool&>(j) == true, "");
  }
  {
    constexpr auto j = ChangeJsonValue(1.5);
    static_assert(j.ToNumber() == 1.5, "");
    static_assert(static_cast<const double&>(j) == 1.5, "");
  }
  {
    constexpr auto j = ChangeJsonValue(cx::StaticString("abc"));
    static_assert(j.ToString() == "abc", "");
    static_assert(static_cast<const cx::StaticString&>(j) == "abc", "");
  }
}

constexpr auto CreateSimpleJson() {
  cx::JsonValue<5> j{};
  j.ToObject();
  j["a"].ToNumber() = 15;
  j["b"].ToString() = "Hello, World!";
  j["d"].ToArray();
  j["c"]["a"]["b"].ToArray().PushBack(10.0);
  j["c"]["a"]["c"] = "Hello, world!";
  j["c"]["a"]["d"].ToArray().PushBack(5.2);
  return j;
}

TEST(JsonvalueTestSuite, TestSimplJson) {
  constexpr auto json = CreateSimpleJson();
  static_assert(json.Size() == 4u, "");
  static_assert(json["a"].ToNumber() == 15.0, "");
  static_assert(json["b"].ToString() == "Hello, World!", "");
  static_assert(json["d"].Size() == 0u, "");
  static_assert(json["d"].GetType() == cx::JsonType::Array, "");
  static_assert(json["c"].Size() == 1u, "");
  static_assert(json["c"]["a"].Size() == 3u, "");
  static_assert(static_cast<double>(json["c"]["a"]["b"][0]) == 10.0, "");
  static_assert(static_cast<cx::StaticString>(json["c"]["a"]["c"]) == "Hello, world!", "");
  static_assert(static_cast<double>(json["c"]["a"]["d"][0]) == 5.2, "");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
