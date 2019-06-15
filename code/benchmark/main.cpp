#include <string>
#include <benchmark/benchmark.h>

static void BM_ShortStringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) {
    std::string copy(x);
  }
}

static void BM_LongStringCopy(benchmark::State& state) {
  std::string x(64, 'a');
  for (auto _ : state) {
    std::string copy(x);
  }
}

BENCHMARK(BM_ShortStringCopy);
BENCHMARK(BM_LongStringCopy);

BENCHMARK_MAIN();
