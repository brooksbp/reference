#include "base/threading/platform_thread.h"

struct thread_params {
	int thread_priority;
	thread_func thread_main;
	void *thread_arg;
};

static
void *thread_launcher(void *arg)
{
	struct thread_params *params = (struct thread_params *) arg;

	if (params->thread_priority != THREAD_PRIORITY_NORMAL)
		platform_thread_set_current_thread_priority(
			params->thread_priority);

	void *ret = params->thread_main(params->thread_arg);

	free(arg);

	return ret;
}

static
int create_thread(
	size_t stack_size, int joinable, thread_func thread_main,
	void *thread_arg, platform_thread_handle_t* thread_handle,
	int thread_priority)
{
	pthread_attr_t attributes;
	pthread_attr_init(&attributes);

	if (!joinable)
		pthread_attr_setdetachstate(
			&attributes, PTHREAD_CREATE_DETACHED);

	if (stack_size == 0)
		stack_size = 2048;

	if (stack_size > 0)
		pthread_attr_setstacksize(&attributes, stack_size);

	struct thread_params *params = calloc(1, sizeof(struct thread_params));
	params->thread_priority = thread_priority;
	params->thread_main = thread_main;
	params->thread_arg = thread_arg;

	pthread_t handle;
	int err = pthread_create(&handle, &attributes, thread_launcher, params);
	if (err) {
		handle = 0;
		errno = err;
	}

	*thread_handle = handle;

	pthread_attr_destroy(&attributes);

	return err;
}

int platform_thread_create_with_priority(
	size_t stack_size, thread_func thread_main, void *thread_arg,
	platform_thread_handle_t *handle, int priority)
{
	return create_thread(stack_size, 1,
			     thread_main, thread_arg, handle, priority);
}

