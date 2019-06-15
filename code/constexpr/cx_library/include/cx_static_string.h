#pragma once

#include <cstddef>
#include <iostream>
#include <algorithm>
#include "cx_algorithm.h"
#include "cx_array.h"

namespace cx {

// static_string is not assumed to be a null terminated string
class static_string {
 public:
  using value_type = char;
  using reference = char&;
  using const_reference = const char&;
  using iterator = const char*;
  using const_iterator = const char*;

  // Constructors

  constexpr static_string() = default;

  // The last character of the input array must be a null character
  template <std::size_t N>
  constexpr explicit static_string(const char (&str)[N]) : size_{N - 1}, data_{&str[0]} {
    STATIC_ASSERT(str[N - 1] == '\0')  // "The last character must be a null character"
  }

  // The last character of the input array must be a null character
  template <std::size_t N>
  constexpr explicit static_string(const cx::array<char, N>& str)
      : size_{N - 1}, data_{str.Data()} {
    STATIC_ASSERT(str[N - 1] == '\0')  // "The last character must be a null character"
  }

  constexpr static_string(const char* str, std::size_t size) : size_{size}, data_{str} {
  }

  // Explicit is not used since sometimes we need to construct it implicitly (e.g. when
  // accessing elements of cx::Map<cx::static_string, ...> with string literals.
  constexpr static_string(const char* str) : size_{GetStringLength(str)}, data_{str} {
  }

  // Iterators

  constexpr const char* begin() const {
    return data_;
  }

  constexpr const char* end() const {
    return data_ + size_;
  }

  constexpr const char* cbegin() const {
    return data_;
  }

  constexpr const char* cend() const {
    return data_ + size_;
  }

  // Accessors

  constexpr char operator[](std::size_t pos) const {
    return STATIC_ASSERT(pos < size_), data_[pos];
  }

  constexpr char at(std::size_t pos) const {
    return STATIC_ASSERT(pos < size_), data_[pos]; // "Index is beyound the size"
  }

  constexpr std::size_t size() const {
    return size_;
  }

  constexpr const char* data() const {
    return data_;
  }

  constexpr cx::static_string substr(std::size_t pos) const {
    STATIC_ASSERT(pos <= size_); // "Substring of negative size is requested"
    return cx::static_string(data_ + pos, size_ - pos);
  }

  constexpr cx::static_string substr(std::size_t pos, std::size_t length) const {
    STATIC_ASSERT(pos + length <= size_); // "Substring of negative size is requested"
    return cx::static_string(data_ + pos, length);
  }

 private:
  const char* data_{nullptr};
  std::size_t size_{0u};
};

constexpr int Compare(const static_string& lhs, const static_string& rhs) {
  for (std::size_t index = 0; index < std::min(lhs.Size(), rhs.Size()); ++index) {
    if (lhs[index] < rhs[index]) {
      return -1;
    } else if (lhs[index] > rhs[index]) {
      return 1;
    }
  }
  if (lhs.Size() < rhs.Size()) {
    return -1;
  } else if (lhs.Size() > rhs.Size()) {
    return 1;
  }
  return 0;
}

constexpr bool operator==(const static_string& lhs, const static_string& rhs) {
  return Compare(lhs, rhs) == 0;
}

constexpr bool operator!=(const static_string& lhs, const static_string& rhs) {
  return Compare(lhs, rhs) != 0;
}

constexpr bool operator<(const static_string& lhs, const static_string& rhs) {
  return Compare(lhs, rhs) < 0;
}

constexpr bool operator>(const static_string& lhs, const static_string& rhs) {
  return Compare(lhs, rhs) > 0;
}

}  // namespace cx
