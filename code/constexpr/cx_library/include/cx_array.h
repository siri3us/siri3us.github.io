#pragma once

#include <cstddef>
#include "cx_algorithm.h"
#include "cx_core.h"

namespace cx {

// TODO: In C++17 use std::array
template <typename Value, std::size_t N>
class array {
 public:
  // TODO: Arrays of size 0 are permitted in C++
  // static_assert(N > 0, "array of zero size is forbidden");

  using value_type = Value;
  using size_type = std::size_t;
  using reference = Value&;
  using const_reference = const Value&;
  using pointer = Value*;
  using const_pointer = const Value*;
  using iterator = Value*;
  using const_iterator = const Value*;

  // Constructors

  constexpr array() noexcept = default;

  constexpr array(const Value (&origin)[N]) noexcept {
    for (std::size_t index = 0; index < N; ++index) {
      data_[index] = origin[index];
    }
  }

  constexpr array(std::initializer_list<Value> init_list) noexcept {
    std::size_t index = 0;
    for (auto& value : init_list) {
      STATIC_ASSERT(index < N);
      data_[index++] = value;
    }
  }

  // Iterators

  constexpr Value* begin() noexcept {
    return STATIC_ASSERT(N > 0), &data_[0];
  }

  constexpr Value* end() noexcept {
    return STATIC_ASSERT(N > 0), &data_[0] + N;
  }

  constexpr const Value* begin() const noexcept {
    return STATIC_ASSERT(N > 0), &data_[0];
  }

  constexpr const Value* end() const noexcept {
    return STATIC_ASSERT(N > 0), &data_[0] + N;
  }

  constexpr const Value* cbegin() const noexcept {
    return STATIC_ASSERT(N > 0), &data_[0];
  }

  constexpr const Value* cend() const noexcept {
    return STATIC_ASSERT(N > 0), &data_[0] + N;
  }

  // Accessors

  constexpr Value& at(std::size_t index) noexcept(false) {
    if (index >= N) {
      throw std::range_error("Index out of range");
    }
    return data_[index];
  }

  constexpr const Value& at(std::size_t index) const noexcept(false) {
    if (index >= N) {
      throw std::range_error("Index out of range");
    }
    return data_[index];
  }

  constexpr Value& operator[](std::size_t index) noexcept {
    return STATIC_ASSERT(index < N), data_[index];
  }

  constexpr const Value& operator[](std::size_t index) const noexcept {
    return STATIC_ASSERT(index < N), data_[index];
  }

  constexpr Value& front() noexcept {
    return STATIC_ASSERT(N > 0), data_[0];
  }

  constexpr Value& back() noexcept {
    return STATIC_ASSERT(N > 0), data_[N - 1];
  }

  constexpr const Value& front() const noexcept {
    return STATIC_ASSERT(N > 0), data_[0];
  }

  constexpr const Value& back() const noexcept {
    return STATIC_ASSERT(N > 0), data_[N - 1];
  }

  // Properties

  constexpr std::size_t size() const noexcept {
    return N;
  }

  constexpr bool empty() const noexcept {
    return N == 0;
  }

  constexpr Value* operator&() noexcept {
    return STATIC_ASSERT(N > 0), &data_[0];
  }

  constexpr const Value* operator&() const noexcept {
    return STATIC_ASSERT(N > 0), &data_[0];
  }

 private:
  Value data_[N] = {};
};

template <typename Value, std::size_t N>
constexpr bool operator==(const array<Value, N>& lhs, const array<Value, N>& rhs) noexcept {
  return cx::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

}  // namespace cx
