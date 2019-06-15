#pragma once

#if defined(__GNUC__)
//#pragma message "Compiling " __FILE__ " with GCC"
#define LIKELY(EXPR) __builtin_expect(!!(EXPR), 1)
#elif defined(__clang__)
//#pragma message "Compiling " __FILE__ " with CLANG"
#define LIKELY(EXPR) __builtin_expect(!!(EXPR), 1)
#else
//#pragma message "Compiling " __FILE__ " with unknown compiler"
#define LIKELY(EXPR) (!!(EXPR))
#endif

#ifdef NDEBUG
//#pragma message "Compiling in NDEBUG mode"
#define STATIC_ASSERT(CHECK) (void(0))
#else
#if __cplusplus > 201402L

// C++17 code here
// #pragma message "Compiling in DEBUG mode with C++17"
#define STATIC_ASSERT(CHECK) (LIKELY(CHECK) ? void(0) : []() { assert(!#CHECK); }())

#else

// C++14 code is here
// #pragma message "Compiling in DEBUG mode with C++14"
static constexpr void assert_impl(const char* condition) {
  assert(!condition);
}
#define STATIC_ASSERT(CHECK) (LIKELY(CHECK) ? void(0) : assert_impl(#CHECK))
  // #define STATIC_ASSERT(CHECK) (LIKELY(CHECK) ? void(0) : throw (#CHECK))

#endif
#endif
