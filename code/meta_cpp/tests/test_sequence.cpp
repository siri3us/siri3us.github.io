#include <gtest/gtest.h>
#include <iostream>
#include "sequence.h"

TEST(SequenceTestSuite, TestIndexSequence) {
  static_assert(seq::CreateIndexSequence<0>().Size() == 0);
  static_assert(seq::CreateIndexSequence<1>().Size() == 1);
  static_assert(seq::CreateIndexSequence<2>().Size() == 2);
  static_assert(seq::CreateIndexSequence<3>().Size() == 3);
  static_assert(seq::CreateIndexSequence<4>().Size() == 4);
  static_assert(seq::CreateIndexSequence<5>().Size() == 5);
}

TEST(SequenceTestSuite, TestInSequence) {
  static_assert(seq::in_sequence_v<int, 1, seq::Sequence<int>> == false);
  static_assert(seq::in_sequence_v<int, 1, seq::Sequence<size_t, 1>> == false);
  static_assert(seq::in_sequence_v<int, 1, seq::Sequence<unsigned, 1u>> == false);

  static_assert(seq::in_sequence_v<int, 0, seq::Sequence<int, 1>> == false);

  static_assert(seq::in_sequence_v<int, 1, seq::Sequence<int, 1>> == true);

  static_assert(seq::in_sequence_v<int, 1, seq::Sequence<int, 1, 2, 3, 4, 5>> == true);
  static_assert(seq::in_sequence_v<int, 2, seq::Sequence<int, 1, 2, 3, 4, 5>> == true);
  static_assert(seq::in_sequence_v<int, 3, seq::Sequence<int, 1, 2, 3, 4, 5>> == true);
  static_assert(seq::in_sequence_v<int, 4, seq::Sequence<int, 1, 2, 3, 4, 5>> == true);
  static_assert(seq::in_sequence_v<int, 5, seq::Sequence<int, 1, 2, 3, 4, 5>> == true);

  static_assert(seq::in_sequence_v<int, 6, seq::Sequence<int, 1, 2, 3, 4, 5>> == false);
  static_assert(seq::in_sequence_v<int, 0, seq::Sequence<int, 1, 2, 3, 4, 5>> == false);
}

TEST(SequenceTestSuite, TestSequenceSize) {
  static_assert(seq::sequence_size_v<seq::Sequence<int, 1, 1, 1>> == 3u);
  static_assert(seq::sequence_size_v<seq::Sequence<int>> == 0u);
  static_assert(seq::sequence_size_v<seq::Sequence<int, 1>> == 1u);
  static_assert(seq::sequence_size_v<seq::Sequence<int, 10, 12, 45, 76, 92>> == 5u);
}

TEST(SequenceTestSuite, TestMaxSequence) {
  static_assert(seq::max_sequence_v<seq::Sequence<int, 4>> == 4);
  static_assert(seq::max_sequence_v<seq::Sequence<int, 1, 1, 1>> == 1);
  static_assert(seq::max_sequence_v<seq::Sequence<int, 2, -1, 10, 43, 1>> == 43);
  static_assert(seq::max_sequence_v<seq::Sequence<int, -1, -2, -3, -4, -5>> == -1);
}

TEST(SequenceTestSuite, TestMinSequence) {
  static_assert(seq::min_sequence_v<seq::Sequence<int, 4>> == 4);
  static_assert(seq::min_sequence_v<seq::Sequence<int, 1, 1, 1>> == 1);
  static_assert(seq::min_sequence_v<seq::Sequence<int, 1, -4, 1>> == -4);
  static_assert(seq::min_sequence_v<seq::Sequence<int, -2, -1, 10, 43, 1>> == -2);
  static_assert(seq::min_sequence_v<seq::Sequence<int, -1, -2, -3, -4, -5>> == -5);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
