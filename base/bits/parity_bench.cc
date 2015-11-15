#include "benchmark/benchmark.h"

#include "base/bits/parity.h"

static volatile int x = 0xF0F0F0F0;

static void BM_parity_scan(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(parity_scan(x));
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_parity_scan);

static void BM_parity_mul(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(parity_mul(x));
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_parity_mul);

static void BM_builtin_parity(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(parity(x));
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_builtin_parity);

BENCHMARK_MAIN();
