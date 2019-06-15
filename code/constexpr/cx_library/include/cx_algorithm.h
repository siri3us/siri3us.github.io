#pragma once

#include <algorithm>
#include <type_traits>

namespace cx {

inline constexpr std::size_t strlen(const char* str) {
  std::size_t size = 0u;
  while (*(str++) != '\0') {
    ++size;
  }
  return size;
}


template <typename It1, typename It2>
constexpr It1 copy(It1 dest, It2 first, It2 last) {
  while (first != last) {
    *(dest++) = *(first++);
  }
  return dest;
}

// "It" is a cheap constructable iterator type
template <typename It, typename UnaryPredicate>
constexpr It find_if(It first, It last, UnaryPredicate predicate) {
  for (; first != last; ++first) {
    if (predicate(*first)) {
      return first;
    }
  }
  return last;
}

template <typename FirstIt, typename SecondIt>
constexpr bool equal(FirstIt begin1, const FirstIt& end1, SecondIt begin2, const SecondIt& end2) {
  while (begin1 != end1 && begin2 != end2) {
    if (*(begin1++) != *(begin2++)) {
      return false;
    }
  }
  return (begin1 == end1) && (begin2 == end2);
}

template <typename FirstIt, typename SecondIt>
constexpr int compare(FirstIt begin1, const FirstIt& end1, SecondIt begin2, const SecondIt& end2) {
  while (begin1 != end1 && begin2 != end2) {
    if (*begin1 < *begin2) {
      return -1;
    } else if (*begin1 > *begin2) {
      return 1;
    }
    ++begin1;
    ++begin2;
  }
  if (begin1 == end1 && begin2 != end2) {
    return -1;
  } else if (begin1 != end1 && begin2 == end2) {
    return 1;
  }
  return 0;
}

}  // namespace cx
