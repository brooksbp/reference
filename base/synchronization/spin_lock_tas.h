#ifndef BASE_SYNCHRONIZATION_TAS_H
#define BASE_SYNCHRONIZATION_TAS_H

struct tas_lock {
	char f;
};

static inline void tas_lock_init(struct tas_lock *lock)
{
	__atomic_store_n(&lock->f, 0, __ATOMIC_RELAXED);
}

static inline void tas_lock_acquire(struct tas_lock *lock)
{
	while (!__atomic_test_and_set(&lock->f, __ATOMIC_RELAXED))
		;  // spin
	__atomic_thread_fence(__ATOMIC_ACQUIRE);
}

static inline void tas_lock_release(struct tas_lock *lock)
{
	__atomic_store_n(&lock->f, 0, __ATOMIC_RELEASE);
}

#endif /* BASE_SYNCHRONIZATION_TAS_H */
