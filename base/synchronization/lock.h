#ifndef BASE_SYNCHRONIZATION_LOCK_H
#define BASE_SYNCHRONIZATION_LOCK_H

#include "base/logging.h"
#include "base/threading/platform_thread.h"

#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct lock {
	platform_thread_ref_t owning_thread_ref;
	pthread_mutex_t handle;
};

static inline
void lock_ctor(struct lock *lock)
{
	lock->owning_thread_ref = 0;
#ifndef NDEBUG
	/* In debug, setup attributes for lock error checking. */
	pthread_mutexattr_t mta;
	int rv = pthread_mutexattr_init(&mta);
	DCHECK(rv == 0);
	rv = pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_ERRORCHECK);
	DCHECK(rv == 0);
	rv = pthread_mutex_init(&lock->handle, &mta);
	DCHECK(rv == 0);
	rv = pthread_mutexattr_destroy(&mta);
	DCHECK(rv == 0);
#else
	pthread_mutex_init(&lock->handle, NULL);
#endif
}

static inline
void lock_dtor(struct lock *lock)
{
	DCHECK(lock->owning_thread_ref == 0);
	int rv = pthread_mutex_destroy(&lock->handle);
	DCHECK(rv == 0);
}

static inline
void lock_assert_acquired(struct lock *lock)
{
	DCHECK(lock->owning_thread_ref == platform_thread_current_ref());
}

static inline
void lock_check_held_and_unmark(struct lock *lock)
{
	DCHECK(lock->owning_thread_ref == platform_thread_current_ref());
	lock->owning_thread_ref = 0;
}

static inline
void lock_check_unheld_and_mark(struct lock *lock)
{
	DCHECK(lock->owning_thread_ref == 0);
	lock->owning_thread_ref = platform_thread_current_ref();
}


static inline
bool lock_try(struct lock *lock)
{
	int rv = pthread_mutex_trylock(&lock->handle);
	DCHECK(rv == 0 || rv == EBUSY);
	if (rv == 0)
		lock_check_unheld_and_mark(lock);
	return rv == 0;
}

static inline
void lock_acquire(struct lock *lock)
{
	int rv = pthread_mutex_lock(&lock->handle);
	DCHECK(rv == 0);
	lock_check_unheld_and_mark(lock);
}

static inline
void lock_release(struct lock *lock)
{
	lock_check_held_and_unmark(lock);
	int rv = pthread_mutex_unlock(&lock->handle);
	DCHECK(rv == 0);
}

#if defined(__cplusplus)
}
#endif

#endif /* BASE_SYNCHRONIZATION_LOCK_H */
