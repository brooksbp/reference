#ifndef CACHE_H
#define CACHE_H

#include "compiler.h"

#define L1_CACHE_SHIFT  6
#define L1_CACHE_BYTES  (1 << L1_CACHE_SHIFT)

#define __cacheline_aligned __aligned(L1_CACHE_BYTES)

#endif  // CACHE_H
