#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <math.h>
#include "Animation.h"
#include "Display.h"
#include "Font.h"
#include "HardwareDisplay.h"
#include "Time.h"
#include "ButtonHandler.h"
#include "SnakeGame.h"


ButtonHandler& buttonHandler = ButtonHandler::getButtonHandler();

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
Frame smiley {smiley_buf};
Frame heart {heart_buf};
Frame rocket {rocket_buf};

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

bool button_l = false;
bool button_r = false;
uint32_t curr_time;
uint32_t last_step { 0 };
uint32_t last_action { 0 };
bool blink { false };

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

    uint8_t i {0};
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

int main() {
    // Disable Watchdog Timer to save power
    wdt_disable();

    init_time();
    display.enable();

    sei();

    demo_multiplexing();

    return 0;
}


ISR(PCINT1_vect) {
    // The interrupt is just used for wakeup. No further actions necessary.
}
