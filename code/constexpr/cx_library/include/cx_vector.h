#pragma once

#include <initializer_list>
#include "cx_array.h"

namespace cx {

template <typename Value, std::size_t MaxSize = 10>
class vector {
  using StorageType = cx::array<Value, MaxSize>;

 public:
  using reference = typename StorageType::reference;
  using const_reference = typename StorageType::const_reference;
  using iterator = typename StorageType::iterator;
  using const_iterator = typename StorageType::const_iterator;

  // Constructors

  constexpr vector() noexcept = default;

  template <typename Iter>
  constexpr vector(Iter first, Iter last) {
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }

  constexpr vector(std::initializer_list<Value> list) : vector(list.begin(), list.end()) {
  }

  // Iterators

  constexpr iterator begin() {
    return data_.begin();
  }

  constexpr iterator end() {
    return data_.begin() + size_;
  }

  constexpr const_iterator begin() const {
    return data_.begin();
  }

  constexpr const_iterator end() const {
    return data_.begin() + size_;
  }

  constexpr const_iterator cbegin() const {
    return data_.cbegin();
  }

  constexpr const_iterator cend() const {
    return data_.cbegin() + size_;
  }

  // Accessors

  constexpr Value& operator[](const std::size_t index) {
    return STATIC_ASSERT(index < size_), data_[index];
  }

  constexpr const Value& operator[](const std::size_t index) const {
    return STATIC_ASSERT(index < size_), data_[index];
  }

  constexpr Value& at(const std::size_t index) noexcept(false) {
    if (index >= size_) {
      throw std::range_error("Index past end of vector");
    } else {
      return data_[index];
    }
  }

  constexpr const Value& at(const std::size_t index) const noexcept(false) {
    if (index >= size_) {
      throw std::range_error("Index past end of vector");
    } else {
      return data_[index];
    }
  }

  constexpr Value& push_back(Value value) {
    STATIC_ASSERT(size_ < MaxSize);
    Value& placeholder = data_[size_++];
    placeholder = std::move(value);
    return placeholder;
  }

  constexpr Value& front() {
    return STATIC_ASSERT(size_ > 0), data_[0];
  }

  constexpr const Value& front() const {
    return STATIC_ASSERT(size_ > 0), data_[0];
  }

  constexpr Value& back() {
    return STATIC_ASSERT(size_ > 0), data_[size_ - 1];
  }

  constexpr const Value& back() const {
    return STATIC_ASSERT(size_ > 0), data_[size_ - 1];
  }

  // Properties

  constexpr std::size_t size() const {
    return size_;
  }

  constexpr std::size_t capacity() const {
    return MaxSize;
  }

  constexpr bool empty() const {
    return size_ == 0;
  }

  constexpr const Value* data() const {
    return &data_;
  }

 private:
  StorageType data_{};
  std::size_t size_{0};
};

template <typename Value, std::size_t MaxSize>
constexpr bool operator==(const cx::vector<Value, MaxSize>& lhs,
                          const cx::vector<Value, MaxSize>& rhs) {
  return cx::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Value, std::size_t MaxSize>
constexpr bool operator!=(const cx::vector<Value, MaxSize>& lhs,
                          const cx::vector<Value, MaxSize>& rhs) {
  return !(lhs == rhs);
}

}  // namespace cx
