#include "benchmark/benchmark.h"

#include "spin_lock/tas.h"

static struct tas_lock f;

static void BM_TAS(benchmark::State& state) {
  while (state.KeepRunning()) {
    for (int i = 0; i < 100000000; ++i) {
      tas_lock_acquire(&f);
      tas_lock_release(&f);
    }
  }
  state.SetItemsProcessed(state.iterations() * 100000000);
}
BENCHMARK(BM_TAS)->ThreadPerCpu();

BENCHMARK_MAIN();
