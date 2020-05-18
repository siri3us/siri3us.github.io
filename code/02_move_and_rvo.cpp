#include <utility>
#include "S.h"

//////////////////////////////////////////////////
S ReturnConstSWithMove() {
  const S s{1};
  return std::move(s);
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=1)
// S(const S&)
// ~S()
// ~S()
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=1)
// S(const S&) Copying to the actually returned value (move not used since it is const)
// ~S()        Destroying local value s{1}
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying returned value
// ~S()        Destroying local variable in main
//////////////////////////////////////////////////

//////////////////////////////////////////////////
S ReturnNonConstSWithMove() {
  S s{1};
  return std::move(s);
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=1)
// S(S&&)    We explicitely asked to move
// ~S()
// ~S()
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=1)
// S(S&&)      Copying to the actually returned value (move not used since it is const)
// ~S()        Destroying local value s{1}
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying returned value
// ~S()        Destroying local variable in main
//////////////////////////////////////////////////

//////////////////////////////////////////////////
S ReturnNonConstSWithNRVO() {
  S s{1};
  return s;
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=1)    Creating returned value in place
// ~S()
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=1)
// S(S&&)      Moving to the actually returned value (move not used since it is const)
// ~S()        Destroying local value s{1}
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying returned value
// ~S()        Destroying local variable in main
//////////////////////////////////////////////////
// (N)RVO reserves the place for the output variable to created it inplace

//////////////////////////////////////////////////
S ReturnConstSWithNRVO() {
  const S s{1};
  return s;
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=1)    Creating returned value in place
// ~S()        Destroying the main's variable
//
// IT IS STILL NRVO (though it is copy elision from the local const object)
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=1)
// S(const S&) Copying to the actually returned value (move not used since it is const)
// ~S()        Destroying local value s{1}
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying returned value
// ~S()        Destroying local variable in main
//////////////////////////////////////////////////

//////////////////////////////////////////////////
S ReturnConstSByCondition(bool condition) {
  if (condition) {
    const S s{1};
    return s;
  } else {
    const S s{0};
    return s;
  }
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=1)    Creating returned value in place
// S(const S&) Copying from the local object directly to the main's object (copy constructor)
// ~S()        Destorying the local variable
// ~S()        Destroying the main's variable
//
// NRVO Cannot be applied here since there is no way to pass preliminarily allocated space to the
// function since the branch prohibits its usage. NRVO required a single object to be returned.
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=1)
// S(const S&) Copying to the actually returned value (move not used since it is const)
// ~S()        Destroying local value s{1}
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying returned value
// ~S()        Destroying local variable in main
//////////////////////////////////////////////////


//////////////////////////////////////////////////
S ReturnNonConstSByCondition(bool condition) {
  if (condition) {
    S s{1};
    return s;
  } else {
    S s{0};
    return s;
  }
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=1)    Creating returned value in place
// S(S&&)      Moving from the local object directly to the main's object (move constructor)
// ~S()        Destorying the local variable
// ~S()        Destroying the main's variable
//
// NRVO Cannot be applied here since there is no way to pass preliminarily allocated space to the
// function since the branch prohibits its usage. NRVO required a single object to be returned.
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=1)
// S(S&&)      Moving to the actually returned value (move not used since it is const)
// ~S()        Destroying local value s{1}
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying returned value
// ~S()        Destroying local variable in main
//////////////////////////////////////////////////


struct T {
  S s;
};

//////////////////////////////////////////////////
S GetSFromNonConstT() {
  T t{2};
  return t.s;
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=2)    Creating T object (S constructor)
// S(const S&) Copying from the local object directly to the main's object (copy constructor)
// ~S()        Destorying the local variable
// ~S()        Destroying the main's variable
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=2)
// S(S&&)
// ~S()
// S(const S&) Copying to the returned value
// ~S()        Destroying local value s{2}
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying returned value
// ~S()        Destroying local variable in main
//////////////////////////////////////////////////

//////////////////////////////////////////////////
S GetSFromNonConstTByMove() {
  T t{3};
  return std::move(t).s;
}
//////////////////////////////////////////////////
// C++17 and C++11/14 without "-fno-elide-constructors" ("-fno-elide-constructors" does not
// matter in C++17 since copy elision is always enabled)
//
// S(int=3)    Creating T object (S constructor)
// S(S&&)      Moving from the local object directly to the main's object (move constructor)
// ~S()        Destorying the local variable
// ~S()        Destroying the main's variable
//
// Member access of rvalue is rvalue
//
//////////////////////////////////////////////////
// C++11/14 with "-fno-elide-constructors"
//
// S(int=3)
// S(S&&)      Creating temporary copy during call to std::move(t).s
// ~S()        Calling desctructor of temporary copy
// S(S&&)      Moving to the returned value
// ~S()        Destroying the local variable
// S(S&&)      Moving to the initialized local object in main function
// ~S()        Destroying the temporary returned value
// ~S()        Destroying the main's local variable
//////////////////////////////////////////////////


// Make return variables non-const
// Use Clang`s -Wmove

int main(int argc, char** argv) {
  // auto s1 = ReturnConstSWithMove();
  // auto s2 = ReturnNonConstSWithMove();
  // auto s3 = ReturnNonConstSWithNRVO();
  // auto s4 = ReturnConstSWithNRVO();
  // auto s51 = ReturnConstSByCondition(true);
  // auto s61 = ReturnNonConstSByCondition(true);
  // auto s7 = GetSFromNonConstT();
  auto s8 = GetSFromNonConstTByMove();

  return 0;
}
