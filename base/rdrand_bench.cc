#include "benchmark/benchmark.h"

#include "base/compiler.h"
#include "base/rdrand.h"

static void bench_rdrand(benchmark::State& state) {
  uint64_t n;
  int success = 1;
  while (state.KeepRunning() && success) {
    success = rdrand64(&n);
    barrier();
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(bench_rdrand);
//BENCHMARK(bench_rdrand)->MinTime(60.0);

BENCHMARK_MAIN();
