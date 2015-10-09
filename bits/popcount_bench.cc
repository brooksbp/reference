#include "benchmark/benchmark.h"

#include "bits/popcount.h"

static const int x = 0xF0F0F0F0;

static void BM_popcount_drop_lsb(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(popcount_drop_lsb(x));
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_popcount_drop_lsb);

static void BM_builtin_popcount(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(popcount(x));
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_builtin_popcount);

BENCHMARK_MAIN();
