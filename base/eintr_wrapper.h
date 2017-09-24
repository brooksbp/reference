#ifndef BASE_EINTR_WRAPPER_H
#define BASE_EINTR_WRAPPER_H

#include <errno.h>

#if defined(NDEBUG)

#define HANDLE_EINTR(x) ({ \
	typeof(x) eintr_wrapper_result; \
	do { \
		eintr_wrapper_result = (x); \
	} while (eintr_wrapper_result == -1 && errno == EINTR); \
	eintr_wrapper_result; \
})

#else

#define HANDLE_EINTR(x) ({ \
	int eintr_wrapper_counter = 0;	\
	typeof(x) eintr_wrapper_result; \
	do { \
		eintr_wrapper_result = (x); \
	} while (eintr_wrapper_result == -1 && errno == EINTR && \
		 eintr_wrapper_counter++ < 100); \
	eintr_wrapper_result; \
})

#endif /* NDEBUG */

#define IGNORE_EINTR(x) ({ \
	typeof(x) eintr_wrapper_result; \
	do { \
		eintr_wrapper_result = (x); \
		if (eintr_wrapper_result == -1 && errno == EINTR) { \
			eintr_wrapper_result = 0; \
		} \
	} while (0); \
	eintr_wrapper_result; \
})

#endif /* BASE_EINTR_WRAPPER_H */
