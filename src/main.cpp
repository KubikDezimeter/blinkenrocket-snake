#include <stdlib.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <math.h>
#include "Display.h"
#include "HardwareDisplay.h"
#include "Time.h"
#include "ButtonHandler.h"
#include "SnakeGame.h"



int delay(const uint8_t score) {
    return 80 * sqrt(-score + 70);
}

int main() {

    // Disable Watchdog Timer to save power
    wdt_disable();

    init_time();
    ButtonHandler& buttonHandler = ButtonHandler::getButtonHandler();
    display.enable();


    SnakeGame game {};

    bool button_l = false;
    bool button_r = false;
    uint32_t last_step { 0 };
    bool blink { false };

    while (true) {
        uint32_t curr_time = time_ms;
        button_l = buttonHandler.update_button_press_l(curr_time);
        button_r = buttonHandler.update_button_press_r(curr_time);

        if (ButtonHandler::get_button_state_l() && ButtonHandler::get_button_state_r()) {
            game = SnakeGame {};
        }

        if (game.isGameover()) {
            if (blink) {
                display.show(game.render());
            } else {
                display.show(Frame {});
            }

            if (curr_time > last_step + delay(game.getScore())) {
                blink = !blink;
                last_step = curr_time;
            }
            continue;
        }

        if (button_l) {
            game.pressLeft();
        }
        if (button_r) {
            game.pressRight();
        }

        if (curr_time > last_step + delay(game.getScore())) {
            game.step();
            last_step = curr_time;
        }
        
        display.show(game.render());
    }


    return 0;
}
