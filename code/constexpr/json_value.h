#include <iostream>
#include <array>

template <typename K, typename V>
struct Element {
  constexpr Element() = default;
  constexpr Element(const K& key, const V& value) : key(key), value(value) {}

  K key;
  V value;
};

// struct StaticString {
//   template <std::size_t N>
//   constexpr StaticString(const char (&str)[N]) : size_(N - 1), data_(str.data()) {
//   }
//
//   constexpr StaticString(const char* str, std::size_t s) : size_(s), data_(str) {
//   }
//
//   constexpr StaticString() = default;
//
//   constexpr size_t Size() const {
//     return size_;
//   }
//
//   constexpr const char* Data() const {
//     return data_;
//   }
//
//   std::size_t size_{0};
//   const char* data_{nullptr};
// };
//

