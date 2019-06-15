#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <benchmark/benchmark.h>

static constexpr int kAtomicsNumber = 32;

struct AtomicNode {
  std::atomic<int> counter;
};

struct alignas(64) AlignedAtomicNode {
  std::atomic<int> counter;
};

AtomicNode g_na_atomics[kAtomicsNumber];
AlignedAtomicNode g_aa_atomics[kAtomicsNumber];

void IncreaseRange(AlignedAtomicNode* nodes, int first, int last) {
  for (int i = 0; i < 10; ++i) {
    int index = first;
    nodes[index].counter.fetch_add(1);
    index++;
    if (index >= last) {
      index = first;
    }
  }
}

static void BM_TestAlignedAtomics(benchmark::State& state) {
  int range = kAtomicsNumber / state.threads;
  int remainder = kAtomicsNumber % state.threads;
  int first_index = -1;
  if (state.thread_index < remainder) {
    first_index = (range + 1) * state.thread_index;
    range += 1;
  } else {
    first_index = remainder + state.thread_index * range;
  }
  int last_index = first_index + range;
  while (state.KeepRunning()) {
    IncreaseRange(g_aa_atomics, first_index, last_index);
  }
}

void IncreaseRange(AtomicNode* nodes, int first, int last) {
  for (int i = 0; i < 10; ++i) {
    int index = first;
    nodes[index].counter.fetch_add(1);
    index++;
    if (index >= last) {
      index = first;
    }
  }
}

static void BM_TestNotAlignedAtomics(benchmark::State& state) {
  int range = kAtomicsNumber / state.threads;
  int remainder = kAtomicsNumber % state.threads;
  int first_index = -1;
  if (state.thread_index < remainder) {
    first_index = (range + 1) * state.thread_index;
    range += 1;
  } else {
    first_index = remainder + state.thread_index * range;
  }
  int last_index = first_index + range;
  while (state.KeepRunning()) {
    IncreaseRange(g_na_atomics, first_index, last_index);
  }
}

BENCHMARK(BM_TestAlignedAtomics)->Arg(kAtomicsNumber)->ThreadRange(1, 16)->UseRealTime();
BENCHMARK(BM_TestNotAlignedAtomics)->Arg(kAtomicsNumber)->ThreadRange(1, 16)->UseRealTime();

BENCHMARK_MAIN();

// template <class A>
// class AtomicVectorFixture : public benchmark::Fixture {
//  public:
//   void SetUp(const benchmark::State& state) {
//     std::cerr << "SetUp by " << state.thread_index << " " << std::this_thread::get_id() <<
//     std::endl; size_ = state.range(0); bool expected_value = false; if
//     (allocated_.compare_exchange_strong(expected_value, true)) { //       counters_ = new
//     AtomicNode[size_];
//       std::cerr << "Allocate" << std::endl;
//       for (int i = 0; i < size_; ++i) {
//         counters_[i].counter.store(0);
//       }
//     }
//   }
//
//   void TearDown(const benchmark::State& state) {
//     bool expected_value = false;
//     std::cerr << "TearDown by " << state.thread_index << " " << std::this_thread::get_id() <<
//     std::endl; if (deallocated_.compare_exchange_strong(expected_value, true)) {
//       std::cerr << "Delete" << std::endl;
//       delete[] counters_;
//     }
//   }
//
//   AtomicNode* counters_;
//   std::atomic<bool> allocated_{false};
//   std::atomic<bool> deallocated_{false};
//   std::size_t size_;
// };
//
// void UpdateAtomicValues(AtomicNode* counters, size_t size) {
//   for (int n = 0; n < 10; ++n) {
//     for (size_t i = 0; i < size; ++i) {
//       counters[i].counter.fetch_add(1);
//     }
//   }
// }
//
// using NAAFix = AtomicVectorFixture<AtomicNode>;
// BENCHMARK_DEFINE_F(NAAFix, NotAlignedTest)(benchmark::State& state) {
//   while (state.KeepRunning()) {
//     UpdateAtomicValues(counters_, size_);
//   }
// }
// BENCHMARK_REGISTER_F(NAAFix, NotAlignedTest)->ThreadRange(1,
// 1)->Arg(1024)->Unit(benchmark::kNanosecond);

// using AAFix = AtomicVectorFixture<AlignedAtomicNode>;
// BENCHMARK_DEFINE_F(AAFix, AlignedTest)(benchmark::State& state) {
//   while (state.KeepRunning()) {
//     UpdateAtomicValues(counters_, size_);
//   }
// }
// BENCHMARK_REGISTER_F(AAFix, AlignedTest)->Arg(1024)->ThreadRange(1,
// 1)->Unit(benchmark::kNanosecond);
