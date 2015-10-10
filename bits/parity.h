#ifndef BITS_PARITY_H
#define BITS_PARITY_H

#ifdef __cplusplus
extern "C" {
#endif

static inline int parity(unsigned int x) {
  return __builtin_parity(x);
}

static inline int parity_scan(unsigned int x) {
  int y = 0;
  y = x ^ (x >> 1);
  y = y ^ (y >> 2);
  y = y ^ (y >> 4);
  y = y ^ (y >> 8);
  y = y ^ (y >> 16);
  return y & 1;
}

static inline int parity_mul(unsigned int x) {
  x = x ^ (x >> 1);
  x = (x ^ (x >> 2)) & 0x11111111;
  x = x * 0x11111111;
  return (x >> 28) & 1;
}

#ifdef __cplusplus
}
#endif

#endif  // BITS_PARITY_H
