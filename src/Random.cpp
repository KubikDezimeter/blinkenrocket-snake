#include "Random.h"

uint32_t seed {0x32489753};
uint32_t* r { &seed };

// Taken from https://en.wikipedia.org/w/index.php?title=Xorshift&oldid=1328892960
/* The state must be initialized to non-zero */
uint32_t xorshift32(uint32_t* r)
{
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	uint32_t x = *r;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return *r = x;
}
