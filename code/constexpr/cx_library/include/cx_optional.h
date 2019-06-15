namespace cx {

template <typename Value>
class optional {
 public:
  using value_type = Value;

  constexpr optional() = default;

  constexpr optional(const Value& value) : initialized_{true}, value_{value} {
  }

  constexpr optional(Value&& value) : initialized_{true}, value_{std::move(value)} {
  }

  constexpr Value& operator*() {
    if (!initialized_) {
      throw std::runtime_error("Using uninitialized value");
    }
    return value_;
  }

  constexpr const Value& operator*() const {
    if (!initialized_) {
      throw std::runtime_error("Using uninitialized value");
    }
    return value_;
  }

  constexpr operator bool() const {
    return initialized_;
  }

  constexpr void reset() {
    initialized_ = false;
  }

  constexpr optional& operator=(const Value& value) {
    initialized_ = true;
    value_ = value;
    return *this;
  }

  constexpr optional& operator=(Value&& value) {
    initialized_ = true;
    value_ = std::move(value);
    return *this;
  }

 private:
  bool initialized_{false};
  Value value_{};
};

}  // namespace cx
