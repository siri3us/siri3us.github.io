#ifdef NOEX
	#define NOEXCEPT noexcept
#else
	#define NOEXCEPT
#endif

class IntegerValue {
  public:
    explicit IntegerValue(int value = 0) NOEXCEPT;

    int GetValue() const NOEXCEPT;

  private:
    int value_;
};


IntegerValue operator+(const IntegerValue& lhs, const IntegerValue& rhs) NOEXCEPT;
