#include "benchmark/benchmark.h"

#include <stdint.h>

const int kIters = 1000000000;

static uint64_t d64;

static inline void clear(void) {
  __atomic_store_n(&d64, 0, __ATOMIC_SEQ_CST);
}

static void BM_faa(benchmark::State& state) {
  clear();
  while (state.KeepRunning()) {
    for (int i = kIters; i > 0; i--) {
      __atomic_fetch_add(&d64, 1, __ATOMIC_SEQ_CST);
    }
  }
}
BENCHMARK(BM_faa)->ThreadPerCpu();

BENCHMARK_MAIN();
