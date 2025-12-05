#ifndef TIME_H
#define TIME_H

#include <avr/interrupt.h>

void init_time();
void wait_ms(const uint32_t ms);

extern volatile uint32_t time_ms;

#endif
