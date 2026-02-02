#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <math.h>
#include "Animation.h"
#include "Display.h"
#include "Font.h"
#include "Frame.h"
#include "HardwareDisplay.h"
#include "SignalRenderer.h"
#include "Time.h"
#include "ButtonHandler.h"
#include "SnakeGame.h"


ButtonHandler& buttonHandler = ButtonHandler::getButtonHandler();
SignalRenderer signalRenderer {3};

const uint8_t empty[8] {};
const Frame empty_frame {};
uint8_t smiley_buf[8] {
    0b00111100,
    0b01111110,
    0b11011011,
    0b11111111,
    0b11111111,
    0b11011011,
    0b01100110,
    0b00111100,
};
uint8_t heart_buf[8] {
    0b00000000,
    0b01101100,
    0b10010010,
    0b10000010,
    0b01000100,
    0b00101000,
    0b00010000,
    0b00000000,
};
uint8_t rocket_buf[8] {
    0b00011000,
    0b00011000,
    0b00100100,
    0b00100100,
    0b00111100,
    0b00111100,
    0b01011010,
    0b01000010,
};
const Frame smiley {smiley_buf};
const Frame heart {heart_buf};
const Frame rocket {rocket_buf};

uint8_t temp_buf[8];
Frame temp_frame {};

uint32_t delays[20] {
    600,
    550,
    500,
    450,
    400,
    350,
    300,
    250,
    200,
    150,
    100,
    80,
    50,
    35,
    20,
    10,
    5,
    2,
};

uint8_t i;
bool button_r_previous = false;
bool button_l = false;
bool button_r = false;
uint32_t curr_time;
uint32_t last_step { 0 };
uint32_t last_action { 0 };
bool blink { false };
uint32_t counter { 0 };

int delay(const uint8_t x) {
    //return 80 * sqrt(-i + 70);
    //return 8000 / (x + 20) - 10;
    return x < sizeof(delays) ? delays[x] : 0;
}

void demo_multiplexing() {
    display.disable();

    while (true) {
        button_r = buttonHandler.update_button_press_r(time_ms);
        if (button_r) {
            break;
        }
    }

    display.show(smiley);

    while (i < (sizeof(delays) / sizeof(uint32_t)) - 1) {
        i = time_ms / 600;
        display.multiplex();
        wait_ms(delay(i));
    }

    display.enable();

    while (true) {
        button_r = buttonHandler.update_button_press_r(time_ms);
        if (button_r) {
            break;
        }
    }

    display.show(heart);

    while (true) {
        button_r = buttonHandler.update_button_press_r(time_ms);
        if (button_r) {
            break;
        }
    }
    
    display.show(rocket);

    while (true) {
        button_r = buttonHandler.update_button_press_r(time_ms);
        if (button_r) {
            break;
        }
    }
}

void demo_bouncing() {
    // setup right button interrupt to read input
    PCMSK1 |= _BV(PCINT11);
    PCICR |= _BV(PCIE1);

    while (true) {
        curr_time = time_ms;

        button_l = buttonHandler.update_button_press_l(curr_time);
        if (button_l) {
            break;
        }

        // render
        temp_frame = signalRenderer.render();
        display.show(temp_frame);

        wait_ms(40);
    }

    PCICR &= ~_BV(PCIE1);
    PCMSK1 &= ~_BV(PCINT11);
}

void demo_counter(bool debounce) {
    counter = 0;

    while (true) {
        // setup
        button_l = buttonHandler.update_button_press_l(time_ms);

        if (button_l) {
            break;
        }

        // get button input
        if (debounce) {
            button_r = buttonHandler.update_button_press_r(time_ms);

            if (button_r) {
                ++counter;
            }
        } else {
            button_r = buttonHandler.get_button_state_r();
            if (button_r && !button_r_previous) {
                ++counter;
            }

            button_r_previous = button_r;
        }

        // render
        for (i = 0; i < 8; ++i) {
            if (i == counter % 8) {
                temp_buf[i] = 0xff;
            } else {
                temp_buf[i] = 0x00;
            }
        }

        temp_frame = Frame { temp_buf };
        temp_frame.transpose();
        display.show(temp_frame);
    }
}

int main() {
    // Disable Watchdog Timer to save power
    wdt_disable();

    init_time();
    display.enable();

    sei();

    //demo_multiplexing();
    demo_bouncing();
    demo_counter(false);
    display.show(empty_frame);
    wait_ms(300);
    demo_counter(true);

    display.disable();
    while (true);

    return 0;
}


ISR(PCINT1_vect) {
    signalRenderer.push(buttonHandler.get_button_state_r());
}
