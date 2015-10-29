#ifndef SYNCHRONIZATION_TAS_H
#define SYNCHRONIZATION_TAS_H

struct tas_lock {
  char f;
};

void tas_lock_init(struct tas_lock *lock) {
  __atomic_store_n(&lock->f, 0, __ATOMIC_RELAXED);
}

void tas_lock_acquire(struct tas_lock *lock) {
  while (!__atomic_test_and_set(&lock->f, __ATOMIC_RELAXED))
    ;  // spin
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
}

void tas_lock_release(struct tas_lock *lock) {
  __atomic_store_n(&lock->f, 0, __ATOMIC_RELEASE);
}

#endif  // SYNCHRONIZATION_TAS_H
