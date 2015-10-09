#ifndef BITS_POPCOUNT_H
#define BITS_POPCOUNT_H

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

#endif  // BITS_POPCOUNT_H
