#ifndef BITS_POWERS_OF_TWO_H
#define BITS_POWERS_OF_TWO_H

#ifdef __cplusplus
extern "C" {
#endif

// Greatest power of 2 less than or equal to x.
static inline unsigned int floor2(unsigned int x) {
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  return x - (x >> 1);
}

// Least power of 2 greater than or equal to x.
static inline unsigned int ceil2(unsigned int x) {
  x = x - 1;
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  return x + 1;
}

#ifdef __cplusplus
}
#endif

#endif  // BITS_POWERS_OF_TWO_H
