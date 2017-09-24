#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#define __USE_LARGEFILE64  /* struct stat64 */

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include <errno.h>
#include <pthread.h>

#include <stdlib.h>
#include <unistd.h>

#if !defined(__cplusplus)
#define false 0
#define true 1
typedef _Bool bool;
#endif

#endif /* BASE_TYPES_H */
