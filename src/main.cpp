#include <stdlib.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "Display.h"
#include "HardwareDisplay.h"
#include "Time.h"
#include "ButtonHandler.h"



int main() {

    // Disable Watchdog Timer to save power
    wdt_disable();

    init_time();
    ButtonHandler& buttonHandler = ButtonHandler::getButtonHandler();
    display.enable();


    const uint8_t smile[] PROGMEM {
        0b00111100,
        0b01111110,
        0b11011011,
        0b11011011,
        0b11111111,
        0b10111101,
        0b01000010,
        0b00111100,
    };

    const uint8_t chess[] PROGMEM {
        0b10101010,
        0b01010101,
        0b10101010,
        0b01010101,
        0b10101010,
        0b01010101,
        0b10101010,
        0b01010101,
    };

    const uint8_t full[] PROGMEM {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111,
    };
    
    const uint8_t left[] PROGMEM {
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
    };

    const uint8_t right[] PROGMEM {
        0b00001111,
        0b00001111,
        0b00001111,
        0b00001111,
        0b00001111,
        0b00001111,
        0b00001111,
        0b00001111,
    };

    const uint8_t empty[] PROGMEM {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
    };

    const Frame smile_f PROGMEM {smile};
    const Frame chess_f PROGMEM {chess};

    const Frame full_f PROGMEM {full};
    const Frame left_f PROGMEM {left};
    const Frame right_f PROGMEM {right};
    const Frame empty_f PROGMEM {empty};
    
    bool button_l = false;
    bool button_r = false;

    while (true) {
        button_l = buttonHandler.get_button_l();
        button_r = buttonHandler.get_button_r();

        if (button_l && button_r) { display.show(chess_f); }
        else { display.show(smile_f); }
        //else if (button_l && !button_r) { display.show(left_f); }
        //else if (!button_l && button_r) { display.show(right_f); }
        //else if (!button_l && !button_r) { display.show(empty_f); }
    }


    return 0;
}
