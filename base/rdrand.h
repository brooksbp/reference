#ifndef BASE_RDRAND_H
#define BASE_RDRAND_H

#include <stdint.h>

static inline int rdrand16(uint16_t *random)
{
	unsigned char err;

	asm volatile("rdrand %0 ; setc %1" : "=r" (*random), "=qm" (err));

	return (int) err;
}

static inline int rdrand32(uint32_t *random)
{
	unsigned char err;

	asm volatile("rdrand %0 ; setc %1" : "=r" (*random), "=qm" (err));

	return (int) err;
}

static inline int rdrand64(uint64_t *random)
{
	unsigned char err;

	asm volatile("rdrand %0 ; setc %1" : "=r" (*random), "=qm" (err));

	return (int) err;
}

#endif /* BASE_RDRAND_H */
