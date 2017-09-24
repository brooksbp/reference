#ifndef BASE_SYNCHRONIZATION_CONDITION_VARIABLE_H
#define BASE_SYNCHRONIZATION_CONDITION_VARIABLE_H

#include "base/logging.h"

#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct condition_variable {
	pthread_cond_t condition;
	pthread_mutex_t mutex;
};

static inline
void condition_variable_ctor(struct condition_variable *cv)
{
	int rv = 0;
	pthread_condattr_t attrs;

	rv = pthread_condattr_init(&attrs);
	DCHECK_EQ(0, rv);
	pthread_condattr_setclock(&attrs, CLOCK_MONOTONIC);
	rv = pthread_cond_init(&cv->condition, &attrs);
	DCHECK_EQ(0, rv);
	pthread_condattr_destroy(&attrs);
}

static inline
void condition_variable_dtor(struct condition_variable *cv)
{
	int rv = pthread_cond_destroy(&cv->condition);
	DCHECK_EQ(0, rv);
}

static inline
void condition_variable_wait(struct condition_variable *cv)
{
	int rv = pthread_cond_wait(&cv->condition, cv->mutex);
}
//void condition_variable_timed_wait(struct condition_variable *cv, int ticks);

static inline
void condition_variable_broadcast(struct condition_variable *cv)
{
	int rv = pthread_cond_broadcast(&cv->condition);
	DCHECK_EQ(0, rv);
}

static inline
void condition_variable_signal(struct condition_variable *cv)
{
	int rv = pthread_cond_signal(&cv->condition);
	DCHECK_EQ(0, rv);
}

#if defined(__cplusplus)
}
#endif

#endif /* BASE_SYNCHRONIZATION_CONDITION_VARIABLE_H */

