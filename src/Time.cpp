#include "Time.h"

volatile uint32_t time_ms = {0};

void init_time() {
    // Set up 1khz interrupt on Timer 1
    cli();

    // WGM1[3:0] = 0100 -> Clear Timer on Compare Match (CTC) mode
    // CS1[2:0] = 001 -> Select clk_io with no prescaling
    TCCR1A = 0;
    TCCR1B = _BV(WGM12)|_BV(CS10);

    // Set top value to 8 Mhz / 1000 hz = 8000 -> Interrupt every ms
    OCR1A = 8294;

    // Set OCIE1A -> Enable interrupt
    TIMSK1 = _BV(OCIE1A);

    sei();

}

void wait_ms(const uint32_t ms) {
    uint32_t start_time = time_ms;
    uint32_t end_time = start_time + ms;
    while (true) {
        if (time_ms >= end_time) { return; }
    }
}


ISR(TIMER1_COMPA_vect) {
    cli();
    ++time_ms;
    sei();
}
