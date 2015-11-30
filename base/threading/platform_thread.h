#ifndef BASE_THREADING_PLATFORM_THREAD_H
#define BASE_THREADING_PLATFORM_THREAD_H

#include "base/types.h"

#include <sys/resource.h>
#include <sys/syscall.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef pid_t platform_thread_id_t;
typedef pthread_t platform_thread_ref_t;
typedef pthread_t platform_thread_handle_t;

typedef void *(*thread_func)(void *thread_arg);

enum {
	THREAD_PRIORITY_REALTIME = -10,
	THREAD_PRIORITY_NORMAL = 0,
	THREAD_PRIORITY_BACKGROUND = 10,
};

struct platform_thread {
};

static inline
platform_thread_id_t platform_thread_current_id()
{
	return syscall(__NR_gettid);
}

static inline
platform_thread_ref_t platform_thread_current_ref()
{
	return pthread_self();
}

static inline
platform_thread_handle_t platform_thread_current_handle()
{
	return pthread_self();
}

static inline
void platform_thread_yield()
{
	sched_yield();
}

static inline
void platform_thread_sleep_ms(int milliseconds)
{
	usleep(milliseconds * 1000);
}

int platform_thread_create_with_priority(
	size_t stack_size, thread_func thread_main, void *thread_arg,
	platform_thread_handle_t *handle, int priority);

static inline
int platform_thread_create(
	size_t stack_size, thread_func thread_main, void *thread_arg,
	platform_thread_handle_t *handle)
{
	return platform_thread_create_with_priority(
		stack_size, thread_main, thread_arg, handle,
		THREAD_PRIORITY_NORMAL);
}

static inline
void platform_thread_join(platform_thread_handle_t thread_handle)
{
	pthread_join(thread_handle, NULL);
}

static inline
void platform_thread_set_current_thread_priority(int priority)
{
	if (setpriority(PRIO_PROCESS, 0, priority)) {
		// LOG
	}
}

#if defined(__cplusplus)
}
#endif

#endif /* BASE_THREADING_PLATFORM_THREAD_H */
