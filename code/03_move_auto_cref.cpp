#include <algorithm>
#include <iostream>
#include "S.h"

namespace algo {

// template<typename T>
// const T& min(const T& lhs, const T& rhs) noexcept {
//   printf("Begin of algo::min(&lhs=%p, &rhs=%p)\n",
//          static_cast<const void*>(&lhs), static_cast<const void*>(&rhs));
//   const auto& res = lhs < rhs ? lhs : rhs;
//   printf("End of algo::min\n");
//   return res;
// }

template<typename L, typename R>
decltype(auto) min(L&& lhs, R&& rhs) noexcept {
  printf("Begin of algo::min(&lhs=%p, &rhs=%p)\n",
         static_cast<const void*>(&lhs), static_cast<const void*>(&rhs));
  return lhs < rhs ? std::forward<L>(lhs) : std::forward<R>(rhs);
}

}  // namespace algo

bool operator<(const S& lhs, const S& rhs) noexcept {
  return lhs.GetValue() < rhs.GetValue();
}

struct A {
 public:
  explicit A(int i) noexcept : s_(i) {}

  auto GetS() const& noexcept -> const S& {
    printf("const S& A::GetS() const -> S(this=%p, int=%d)\n",
           static_cast<const void*>(&s_), s_.GetValue());
    return s_;
  }

  // This method does not solve the problem with std::min however it tries to prevent
  // creating references to temporary value
  auto GetS() && noexcept -> S {
    printf("S A::GetS() const -> S(%d)\n", s_.GetValue());
    return s_;
  }

 private:
  S s_;
};

int main(int argc, char** argv) {
  const auto& s = algo::min(A(1).GetS(), A(2).GetS());
  // const auto s = algo::min(A(1).GetS(), A(2).GetS());
  printf("min S = S(this=%p, int=%d)\n", static_cast<const void*>(&s), s.GetValue());
  return 0;
}
