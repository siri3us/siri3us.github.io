#include <gtest/gtest.h>
#include "cx_eval.h"

using cx::operator""_eval;

void TestRuntimeExpression(const char* str, double expected_result) {
    std::size_t pos = 0;
    auto expr = cx::StaticString(str);
    auto result = cx::eval::Evaluate(pos, expr);
    EXPECT_EQ(pos, expr.Size());
    EXPECT_EQ(result, expected_result);
}

void TestThrowingRuntimeExpression(const char* str) {
    std::size_t pos = 0;
    auto expr = cx::StaticString(str);
    EXPECT_THROW(cx::eval::Evaluate(pos, expr), std::runtime_error);
}


TEST(EvalRuntimeTestSuite, TestSimpleUnaryExpression) {
  TestRuntimeExpression("1", 1);
  TestRuntimeExpression("2", 2);
  TestRuntimeExpression("12344", 12344);
  TestRuntimeExpression("-12344", -12344);
  TestRuntimeExpression("- 12344 ", -12344);
  TestRuntimeExpression(" \n\n-\t4\t\t ", -4);
  TestRuntimeExpression("-\t4\t\t ", -4);

  TestThrowingRuntimeExpression("1 -");
  TestThrowingRuntimeExpression("1 =");
  TestThrowingRuntimeExpression(" = 1");
  TestThrowingRuntimeExpression("- 1 +");
  TestThrowingRuntimeExpression("--- 1");
  TestThrowingRuntimeExpression("1 2");
  TestThrowingRuntimeExpression("1 + 2 -");
}

TEST(EvalRuntimeTestSuite, TestSimpleBinaryExpression) {
  TestRuntimeExpression("1+2", 3);
  TestRuntimeExpression("1-2", -1);
  TestRuntimeExpression("5*2", 10);
  TestRuntimeExpression("5/2", 2.5);
  TestRuntimeExpression("-5/2", -2.5);
  TestRuntimeExpression("5/2/2", 1.25);

  TestThrowingRuntimeExpression("-5/-2");
  TestThrowingRuntimeExpression("- 5 / - 2 ");
  TestThrowingRuntimeExpression("- 5 / --- 2 ");
  TestThrowingRuntimeExpression("- 5 / --- 2 ");
}

TEST(TestRuntimeTestSuite, TestBinaryExpression) {
  TestRuntimeExpression("1+2*2", 5);
  TestRuntimeExpression("1/2-2", -1.5);
  TestRuntimeExpression("5/2*2 - 1", 4);
  TestRuntimeExpression("5/2^2", 1.25);
}

TEST(TestRuntimeTestSuite, TestParenthisedExpression) {
  TestRuntimeExpression("(1 + 2)", 3);
  TestRuntimeExpression("-(1 + 2)", -3);
  TestRuntimeExpression("-(-1 - 2)", 3);
  TestRuntimeExpression("-(-1 - 2) * 2", 6);
  TestRuntimeExpression("-(-1 - 2) * (-2)", -6);
  TestRuntimeExpression("(-1 - 2)^2", 9);
  TestRuntimeExpression("18/(-1 - 2)^2", 2);

  // Very strange but made on purpose
  TestRuntimeExpression("18/(-1 - 2)^2*5", 10);
  TestRuntimeExpression("((((3 - 5) * 2 + 1) ^ 2 + 1) / 5 + 1)", 3);
  TestRuntimeExpression("1 + 1 + 1 + 1 + 1 + 1", 6);
  TestRuntimeExpression("1 + (2 + (3 + (4 + 5)))", 15);
  TestRuntimeExpression("(1 + 7) / (4 - 2)^2", 2);
  TestRuntimeExpression("(1 + 7)^2 / (4 - 2)^2", 16);
}

TEST(RunTimeEvalTestSuite, TestLiterals) {
  EXPECT_EQ("1 + 2"_eval, 3);
  EXPECT_EQ("(1 + 2)"_eval, 3);
  EXPECT_EQ("-(1 + 2)"_eval, -3);
  EXPECT_EQ("-(-1 - 2)"_eval, 3);
  EXPECT_EQ("-(-1 - 2) * 2"_eval, 6);
  EXPECT_EQ("-(-1 - 2) * (-2)"_eval, -6);
  EXPECT_EQ("(-1 - 2)^2"_eval, 9);
  EXPECT_EQ("18/(-1 - 2)^2"_eval, 2);

  EXPECT_THROW("1 ="_eval, std::runtime_error);
  EXPECT_THROW("1 -"_eval, std::runtime_error);
  EXPECT_THROW("- - 1"_eval, std::runtime_error);
  EXPECT_THROW("-(1 + 2))"_eval, std::runtime_error);
  EXPECT_THROW("-(1 ++ 2))"_eval, std::runtime_error);
  EXPECT_THROW("(-(1 + 2)"_eval, std::runtime_error);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
