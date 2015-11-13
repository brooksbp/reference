#ifndef RANDOM_RDRAND_H
#define RANDOM_RDRAND_H

#include <stdint.h>

int rdrand16(uint16_t *random)
{
	unsigned char err;

	asm volatile("rdrand %0 ; setc %1" : "=r" (*random), "=qm" (err));

	return (int) err;
}

int rdrand32(uint32_t *random)
{
	unsigned char err;

	asm volatile("rdrand %0 ; setc %1" : "=r" (*random), "=qm" (err));

	return (int) err;
}

int rdrand64(uint64_t *random)
{
	unsigned char err;

	asm volatile("rdrand %0 ; setc %1" : "=r" (*random), "=qm" (err));

	return (int) err;
}

#endif  // RANDOM_RDRAND_H
