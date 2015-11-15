#ifndef BASE_PREFETCH_H
#define BASE_PREFETCH_H

#include "base/cache.h"

/*
 * prefetch(x) attempts to pre-emptively get the memory pointed to
 * by address x into the CPU L1 cache.
 */

#define prefetch(x) __builtin_prefetch(x,0)
#define prefetchw(x) __builtin_prefetch(x,1)

static inline void prefetch_range(void *addr, size_t len)
{
	char *cp;
	char *end = addr + len;

	for (cp = addr; cp < end; cp += L1_CACHE_BYTES)
		prefetch(cp);
}

#endif /* BASE_PREFETCH_H */
