#ifndef COMPILE_TIME_MACROS_H
#define COMPILE_TIME_MACROS_H

/* Number of elements in an array */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MAX(x, b)                               \
  ({                                            \
    __typeof__(a) temp_a = (a);                 \
    __typeof__(b) temp_b = (b);                 \
    temp_a > temp_b ? temp_a : temp_b;          \
  })

#define MIN(x, b)                               \
  ({                                            \
    __typeof__(a) temp_a = (a);                 \
    __typeof__(b) temp_b = (b);                 \
    temp_a < temp_b ? temp_a : temp_b;          \
  })

#endif  // COMPILE_TIME_MACROS_H
