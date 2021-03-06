#ifndef BASE_BITS_PARITY_H
#define BASE_BITS_PARITY_H

static inline int parity(unsigned int x)
{
	return __builtin_parity(x);
}

static inline int parity_scan(unsigned int x)
{
	int y = 0;
	y = x ^ (x >> 1);
	y = y ^ (y >> 2);
	y = y ^ (y >> 4);
	y = y ^ (y >> 8);
	y = y ^ (y >> 16);
	return y & 1;
}

static inline int parity_mul(unsigned int x)
{
	x = x ^ (x >> 1);
	x = (x ^ (x >> 2)) & 0x11111111;
	x = x * 0x11111111;
	return (x >> 28) & 1;
}

#endif /* BASE_BITS_PARITY_H */
