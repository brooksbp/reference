#include "benchmark/benchmark.h"

#include "base/cache.h"

#include "base/synchronization/spin_lock_mcs.h"
#include "base/synchronization/spin_lock_tas.h"
#include "base/synchronization/spin_lock_ticket.h"

const int kNumCriticalSections = 10000000;

static struct tas_lock f __cacheline_aligned;

static void BM_TAS(benchmark::State& state) {
  while (state.KeepRunning()) {
    for (int i = 0; i < kNumCriticalSections; ++i) {
      tas_lock_acquire(&f);
      tas_lock_release(&f);
    }
  }
  state.SetItemsProcessed(state.iterations() * kNumCriticalSections);
}
BENCHMARK(BM_TAS)->ThreadPerCpu();

static struct ticket_lock t1 __cacheline_aligned;

static void BM_TicketLock(benchmark::State& state) {
  while (state.KeepRunning()) {
    for (int i = 0; i < kNumCriticalSections; ++i) {
      ticket_lock_acquire(&t1);
      ticket_lock_release(&t1);
    }
  }
  state.SetItemsProcessed(state.iterations() * kNumCriticalSections);
}
BENCHMARK(BM_TicketLock)->ThreadPerCpu();

static struct ticket_lock t2 __cacheline_aligned;

static void BM_TicketLockBackoff(benchmark::State& state) {
  while (state.KeepRunning()) {
    for (int i = 0; i < kNumCriticalSections; ++i) {
      ticket_lock_acquire_bo(&t2, state.range_x());
      ticket_lock_release(&t2);
    }
  }
  state.SetItemsProcessed(state.iterations() * kNumCriticalSections);
}
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<1)->ThreadPerCpu();
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<2)->ThreadPerCpu();
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<3)->ThreadPerCpu();
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<4)->ThreadPerCpu();
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<5)->ThreadPerCpu();
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<6)->ThreadPerCpu();
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<7)->ThreadPerCpu();
BENCHMARK(BM_TicketLockBackoff)->Arg(1<<8)->ThreadPerCpu();

static struct mcs_lock m1 __cacheline_aligned;

static void BM_MCS(benchmark::State& state) {
  struct qnode p __cacheline_aligned;
  while (state.KeepRunning()) {
    for (int i = 0; i < kNumCriticalSections; ++i) {
      mcs_lock_acquire(&m1, &p);
      mcs_lock_release(&m1, &p);
    }
  }
  state.SetItemsProcessed(state.iterations() * kNumCriticalSections);
}
BENCHMARK(BM_MCS)->ThreadPerCpu();

BENCHMARK_MAIN();
