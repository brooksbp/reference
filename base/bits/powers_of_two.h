#ifndef BASE_BITS_POWERS_OF_TWO_H
#define BASE_BITS_POWERS_OF_TWO_H

/* Greatest power of 2 less than or equal to x. */
static inline unsigned int floor2(unsigned int x)
{
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x - (x >> 1);
}

/* Least power of 2 greater than or equal to x. */
static inline unsigned int ceil2(unsigned int x)
{
	x = x - 1;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >> 16);
	return x + 1;
}

#endif /* BASE_BITS_POWERS_OF_TWO_H */
