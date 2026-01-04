#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

// Taken from https://en.wikipedia.org/w/index.php?title=Xorshift&oldid=1328892960
/* The state must be initialized to non-zero */
uint32_t xorshift32(uint32_t* r);

extern uint32_t* r;

#endif
