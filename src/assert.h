#ifndef ASSERT
#define ASSERT

#include <avr/interrupt.h>

inline extern void __assert_fail () {
    cli();
    while(true);
}

#define assert(condition) (static_cast<bool>(condition) ? void (0) : __assert_fail())

#endif
