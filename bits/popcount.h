#ifndef BITS_POPCOUNT_H
#define BITS_POPCOUNT_H

#ifdef __cplusplus
extern "C" {
#endif

static inline int popcount(unsigned int x) {
  return __builtin_popcount(x);
}

static inline int popcount_drop_lsb(unsigned int x) {
  int n = 0;
  while (x) {
    n++;
    x = x & (x - 1);
  }
  return n;
}

#ifdef __cplusplus
}
#endif

#endif  // BITS_POPCOUNT_H
