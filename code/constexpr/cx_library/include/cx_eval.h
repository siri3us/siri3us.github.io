#include <cstddef>
#include <iostream>
#include <sstream>
#include "cx_pair.h"
#include "cx_optional.h"
#include "cx_alpha.h"
#include "cx_static_string.h"

namespace cx {
namespace eval {

constexpr bool IsBinaryOperator(char op) {
  return op == '*' || op == '/' || op == '+' || op == '-' || op == '^';
}

constexpr bool IsUnaryOperator(char op) {
  return op == '+' || op == '-';
}

constexpr int GetOperatorPriority(char c) {
  if (c == '+' || c == '-') {
    return 0;
  } else if (c == '*' || c == '/') {
    return 1;
  } else if (c == '^') {
    return 2;
  } else {
    throw std::runtime_error("Unknown operator");
  }
}

constexpr double ApplyBinaryOperator(char op, double lhs, double rhs) {
  if (op == '+') {
    return lhs + rhs;
  } else if (op == '-') {
    return lhs - rhs;
  } else if (op == '*') {
    return lhs * rhs;
  } else if (op == '/') {
    return lhs / rhs;
  } else if (op == '^') {
    if (static_cast<int>(rhs) != rhs) {
      throw std::runtime_error("Power must be an integer number");
    }
    if (lhs == 0) {
      throw std::runtime_error("Cannot calculate power of 0");
    }
    double result = 1;
    for (int i = 0; i < rhs; ++i) {
      result *= lhs;
    }
    return result;
  }
  throw std::runtime_error("Unknown binary operator");
}

constexpr double ApplyUnaryOperator(char op, double value) {
  if (op == '-') {
    return -value;
  } else if (op == '+') {
    return value;
  } else {
    throw std::runtime_error("Unknown unary operation code");
  }
}

// @detail Calculates all flat expressions which priority is higher than "priority"
// @param pos
// @param expr
// @param priority Applying only operations with priority higher than this value
constexpr double Evaluate(std::size_t& pos, const cx::StaticString& expr, int priority = -1) {
  cx::optional<double> result;
  while (pos < expr.Size()) {
    char c = expr[pos];
    // 1. Skipping whitespace symbols
    if (alpha::IsWhitespace(c)) {
      ++pos;
      continue;
    }
    // 2. Considering new lexem
    if (result) {
      // Some value has been already calculated
      if (IsBinaryOperator(c)) {
        if (GetOperatorPriority(c) > priority) {
          result = ApplyBinaryOperator(c, *result, Evaluate(++pos, expr, GetOperatorPriority(c)));
        } else {
          return *result;
        }
      } else if (c == ')') {
        return *result;
      } else {
        throw std::runtime_error("Expected binary operator or closing brace");
      }
    } else {
      if (IsUnaryOperator(c)) {
        if (GetOperatorPriority(c) > priority) {
          result = ApplyUnaryOperator(c, Evaluate(++pos, expr, GetOperatorPriority(c)));
        } else {
          throw std::runtime_error("Cannot evaluate unary operator");
        }
      } else if (alpha::IsNumber(c)) {
        result = c - '0';
        for (++pos; pos < expr.Size() && alpha::IsNumber(expr[pos]); ++pos) {
          result = *result * 10 + expr[pos] - '0';
        }
      } else if (c == '(') {
        result = Evaluate(++pos, expr);
        if (pos == expr.Size() || expr[pos] != ')') {
          throw std::runtime_error("Unbalanced parenthesis");
        } else {
          ++pos;
        }
      } else {
        throw std::runtime_error("Unknown symbol");
      }
    }
  }
  if (!result) {
    throw std::runtime_error("Empty result of expression");
  }
  return *result;
}

}  // namespace eval

constexpr double operator""_eval(const char* str, std::size_t size) {
  std::size_t pos = 0;
  double result = eval::Evaluate(pos, cx::StaticString(str, size));
  if (pos != size) {
    throw std::runtime_error("Expression is fully evaluted");
  }
  return result;
}

}  // namespace cx
