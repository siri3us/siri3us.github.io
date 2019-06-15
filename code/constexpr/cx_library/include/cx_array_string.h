#pragma once

#include <cstddef>
#include "cx_array.h"
#include "cx_algorithm.h"

namespace cx {

// array_string is always a null terminated string.
// It keeps its own copy of the data.
template <std::size_t MaxSize>
class array_string {
 public:
  using storage_type = cx::array<char, MaxSize + 1>;
  using iterator = typename storage_type::iterator;
  using const_iterator = typename storage_type::const_iterator;
  using reference = typename storage_type::reference;
  using const_reference = typename storage_type::const_reference;

  // Constructors
  constexpr array_string() = default;

  template <std::size_t N>
  constexpr explicit array_string(const char (&str)[N]) noexcept {
    // The last character must be a null character
    STATIC_ASSERT(str[N - 1] == '\0');
    for (std::size_t index = 0; index < N; ++index) {
      data_[index] = str[index];
    }
  }

  template <typename It>
  constexpr array_string(It first, It last) noexcept {
    cx::copy(begin(), first, last);
  }

  // constexpr explicit array_string(const StaticString& str) : data_{str.cbegin(), str.cend()} {
  //   if (str.Size() >= MaxSize) {
  //     throw std::runtime_error("The last character must be a null character");
  //   }
  // }

  // Operators
  // constexpr array_string& operator=(const StaticString& str) {
  //   return *this = array_string(str.cbegin(), str.cend());
  // }

  constexpr char& operator[] (std::size_t index) noexcept {
    return STATIC_ASSERT(index < MaxSize), data_[index];
  }

  constexpr char operator[] (std::size_t index) const noexcept {
    return STATIC_ASSERT(index < MaxSize), data_[index];
  }

  constexpr iterator begin() noexcept {
    return data_.begin();
  }

  constexpr const_iterator begin() const noexcept {
    return data_.begin();
  }

  constexpr iterator end() noexcept {
    return data_.end();
  }

  constexpr const_iterator end() const noexcept {
    return data_.end();
  }

  constexpr std::size_t size() const noexcept {
    return MaxSize;
  }

 private:
  storage_type data_{};
};

template <std::size_t N1, std::size_t N2>
constexpr array_string<N1 + N2> operator+(const array_string<N1>& lhs,
                                          const array_string<N2>& rhs) noexcept {
  cx::array_string<N1 + N2> result;
  std::size_t index1 = 0;
  while (index1 < lhs.size() && lhs[index1] != '\0') {
    result[index1] = lhs[index1];
    index1++;
  }
  std::size_t index2 = 0;
  while (index2 < rhs.size() && rhs[index2] != '\0') {
    result[index1 + index2] = rhs[index2];
    index2++;
  }
  return result;
}

}  // namespace cx
