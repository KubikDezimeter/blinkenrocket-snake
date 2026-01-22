#include "HardwareDisplay.h"

HardwareDisplay display;

void HardwareDisplay::enable() {
    // Ports B and D drive the dot matrix display -> set all as output
    DDRB = 0xff;
    DDRD = 0xff;

    // Enable 8bit counter with prescaler=8 (-> timer frequency = 1MHz)
    TCCR0A = _BV(CS01);

    // raise timer interrupt on counter overflow (-> interrupt frequency = ~4kHz)
    TIMSK0 = _BV(TOIE0);
}

void HardwareDisplay::disable() {
    // disable counter interrupts
    TIMSK0 &= ~_BV(TOIE0);
    PORTB = 0x00;
    PORTD = 0x00;
}

void HardwareDisplay::show(const Frame frame) const {
    display.frame = frame;
}

/*
 * LED is on when current flows from port B (columns) to port D (rows)
 * -> LEDs in [schematic](https://github.com/blinkenrocket/hardware/blob/master/blinkenrocket_cr2032.pdf) seem to be flipped
 *
 * Pin order with rocket tip pointing up
 *    B01234567
 *   D7        
 *   D6        
 *   D5        
 *   D4        
 *   D3        
 *   D2        
 *   D1        
 *   D0        
 */
void HardwareDisplay::multiplex() {
    PORTD = 255;
    uint8_t row = frame.rowByte(activeRow);
    // Reverse bitorder
    row = (row & 0xF0) >> 4 | (row & 0x0F) << 4;
    row = (row & 0xCC) >> 2 | (row & 0x33) << 2;
    row = (row & 0xAA) >> 1 | (row & 0x55) << 1;
    PORTB = row;
    PORTD = _BV(7 - activeRow) ^ 255;

    if (++activeRow == 8) {
        activeRow = 0;
    }
}

/*
 * Current configuration:
 * One interrupt per 256 microseconds. The whole display is refreshed every
 * 2048us, giving a refresh rate of ~500Hz
 */
ISR(TIMER0_OVF_vect)
{
    display.multiplex();
}
