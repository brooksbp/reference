#ifndef BASE_CACHE_H
#define BASE_CACHE_H

#include "base/compiler.h"

#define L1_CACHE_SHIFT  6
#define L1_CACHE_BYTES  (1 << L1_CACHE_SHIFT)

#define __cacheline_aligned __aligned(L1_CACHE_BYTES)

#endif /* BASE_CACHE_H */
