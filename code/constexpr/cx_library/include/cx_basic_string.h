#pragma once

#include <algorithm>
#include <cstddef>
#include "cx_vector.h"

namespace cx {

// basic_string is always a null terminated string.
// It keeps its own copy of the data.
template <std::size_t MaxSize>
class basic_string : public Vector<MaxSize> {
 public:
  // Constructors
  constexpr basic_string() = default;

  template <std::size_t N>
  constexpr explicit basic_string(const char (&str)[N]) : Vector<MaxSize>(&str[0], &str[N - 1]) {
    if (str[N - 1] != '\0' && N >= MaxSize) {
      throw std::runtime_error("The last character must be a null character");
    }
  }

  constexpr explicit basic_string(const StaticString& str)
      : Vector<MaxSize>{str.cbegin(), str.cend()} {
    if (str.Size() >= MaxSize) {
      throw std::runtime_error("The last character must be a null character");
    }
  }

  constexpr basic_string& operator=(const StaticString& str) {
    return *this = basic_string(str.cbegin(), str.cend());
  }

  template <typename It>
  constexpr basic_string& append(It first, It last) {
    Vector<MaxSize>::append(first, last);
    return *this;
  }

  constexpr basic_string& append(const char* str) {
    while (*str != '\0') {
      push_back(*str);
    }
    return *this;
  }

  constexpr basic_string& append(const char* str, std::size_t n) {
    while (n-- > 1) {
      push_back(*str);
    }
    push_back(*str);
    return *this;
  };

  constexpr basic_string& append(std::size_t n, char c) {
    while (n-- > 1) {
      push_back(c);
    }
    return c;
  }

  template <std::size_t N1, std::size_t N2>
  constexpr basic_string<N1 + N2> operator+(const basic_string<N1>& lhs,
                                            const basic_string<N2>& rhs) {
    basic_string<N1 + N2> result(lhs.begin(), lhs.end());
    result.append(rhs.begin(), rhs.end());
    return result;
  }

}  // namespace cx
