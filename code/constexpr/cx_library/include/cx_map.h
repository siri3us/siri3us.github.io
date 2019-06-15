#include <array>
#include <stdexcept>
#include "cx_pair.h"
#include "cx_array.h"

namespace cx {

template <typename Key, typename Value, std::size_t MaxSize = 10,
          typename Comp = std::equal_to<Key>>
class Map {
  using StorageType = cx::Array<cx::Pair<Key, Value>, MaxSize>;

 public:
  using iterator = typename StorageType::iterator;
  using const_iterator = typename StorageType::const_iterator;
  using reference = typename StorageType::reference;
  using const_reference = typename StorageType::const_reference;

  // Constructors

  constexpr Map() = default;
  constexpr Map(std::initializer_list<cx::Pair<Key, Value>> init_list)
      : data_(init_list.begin(), init_list.end()), size_{init_list.size()} {
  }

  // Iterators

  constexpr iterator begin() {
    return data_.begin();
  }

  constexpr iterator end() {
    return data_.end();
  }

  constexpr const_iterator begin() const {
    return data_.begin();
  }

  constexpr const_iterator end() const {
    return data_.end();
  }

  constexpr const_iterator cbegin() const {
    return data_.cbegin();
  }

  constexpr const_iterator cend() const {
    return data_.cend();
  }

  // Accessors

  constexpr Value& operator[](const Key& key) {
    auto it = Find(key);
    if (it != end()) {
      return it->second;
    } else {
      if (size_ >= MaxSize) {
        throw std::runtime_error("Cannot insert element into the full map");
      }
      data_[size_].first = key;
      return data_[size_++].second;
    }
  }

  constexpr const Value& operator[](const Key& key) const {
    return At(key);
  }

  constexpr const Value& At(const Key& key) const {
    auto it = Find(key);
    if (it != end()) {
      return it->second;
    } else {
      throw std::range_error("Key not found");
    }
  }

  constexpr iterator Find(const Key& key) {
    return FindImpl(key);
  }

  constexpr const_iterator Find(const Key& key) const {
    return FindImpl(key);
  }

  constexpr bool Erase(const Key& key) {
    std::size_t index = 0;
    for (; index < size_; ++index) {
      if (data_[index].first == key) {
        break;
      }
    }
    if (index < size_) {
      for (; index + 1 < size_; ++index) {
        data_[index] = data_[index + 1];
      }
      --size_;
      return true;
    } else {
      return false;
    }
  }

  constexpr std::size_t Size() const {
    return size_;
  }

  constexpr bool Empty() const {
    return size_ == 0;
  }

  constexpr cx::Pair<Key, Value>& GetByIndex(std::size_t index) {
    return data_[index];
  }

  constexpr const cx::Pair<Key, Value>& GetByIndex(std::size_t index) const {
    return data_[index];
  }

 private:
  constexpr const_iterator FindImpl(const Key& key) const {
    Comp comp{};
    for (auto it = data_.begin(); it != data_.end(); ++it) {
      if (comp(it->first, key)) {
        return it;
      }
    }
    return data_.end();
  }

  // Remove duplication
  constexpr iterator FindImpl(const Key& key) {
    Comp comp{};
    for (auto it = data_.begin(); it != data_.end(); ++it) {
      if (comp(it->first, key)) {
        return it;
      }
    }
    return data_.end();
  }

  std::size_t size_{0};
  StorageType data_{};
};

template <typename Key, typename Value, std::size_t MaxSize>
constexpr bool operator==(const Map<Key, Value, MaxSize>& lhs,
                          const Map<Key, Value, MaxSize>& rhs) {
  return Equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename Value, std::size_t MaxSize>
constexpr bool operator!=(const Map<Key, Value, MaxSize>& lhs,
                          const Map<Key, Value, MaxSize>& rhs) {
  return !(lhs == rhs);
}

}  // namespace cx
