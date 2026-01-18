#include <stdlib.h>
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
SnakeGame game {};

const uint8_t score_message[] {
    0x32,0x49,0x49,0x49,0x26,
    0x00,
    0x0E,0x11,0x11,0x11,0x0A,
    0x00,
    0x0E,0x11,0x11,0x11,0x0E,
    0x00,
    0x1F,0x04,0x08,0x10,0x10,
    0x00,
    0x0E,0x15,0x15,0x15,0x0C,
    0x00,
    0x12,
    0x00,0x00,0x00,
};
const uint8_t empty[8] {};
const Frame empty_frame {};
uint8_t score_buffer[8+sizeof(score_message)+2*6] {};
Animation score {score_buffer, 8, sizeof(score_buffer)};

bool button_l = false;
bool button_r = false;
uint32_t curr_time;
uint32_t last_step { 0 };
uint32_t last_action { 0 };
bool blink { false };


void reset_score() {
    score.reset();
    score.append(empty, sizeof(empty));
    score.append(score_message, sizeof(score_message));
}

int delay(const uint8_t score) {
    return 80 * sqrt(-score + 70);
}

void sleep() {
    display.disable();

    // Setup Pin Change Interrupts for Button pins (PC3/PCINT11 and PC7/PCINT15)
    PCMSK1 |= _BV(PCINT11) | _BV(PCINT15);
    PCICR |= _BV(PCIE1);  // PCINT1 is used for pins PCINT[15:8]

    // Go to sleep
    SMCR |= _BV(SM1) | _BV(SE);  // Set Sleep mode Power-down and enable sleep instruction
    asm("sleep");

    // (wakeup)

    // Reset sleep enable bit
    SMCR &= ~_BV(SE);

    // Disable Pin Change Interrupts again
    PCICR &= ~_BV(PCIE1);
    PCMSK1 &= ~(_BV(PCINT11) | _BV(PCINT15));

    display.enable();

    // Wait for wakeup buttons to be released again
    while (ButtonHandler::get_button_state_l() || ButtonHandler::get_button_state_r());
    wait_ms(50);  // Wait a moment for buttons to stop bouncing
}

int main() {

    // Disable Watchdog Timer to save power
    wdt_disable();

    init_time();
    display.enable();

    sei();

    reset_score();

    while (true) {
        curr_time = time_ms;
        button_l = buttonHandler.update_button_press_l(curr_time);
        button_r = buttonHandler.update_button_press_r(curr_time);

        if (ButtonHandler::get_button_state_l() || ButtonHandler::get_button_state_r()) {
            last_action = curr_time;
        }

        if (ButtonHandler::get_button_state_l() && ButtonHandler::get_button_state_r()) {
            game.reset();
            reset_score();
            last_step = curr_time;
            display.show(game.render());  // Render for blinking
            continue;
        }

        if (game.isGameover()) {
            // Go to sleep 30 seconds after last action
            if (last_action + 30000 < curr_time) {
                sleep();
                last_action = curr_time;
            }

            // Append score to score animation if necessary
            if (score.getColCount() == 8+sizeof(score_message)) {
                uint8_t gamescore = game.getScore();
                if (gamescore < 10) {
                    score.append(gamescore);
                    score.append(empty, sizeof(empty));
                } else {
                    score.append(gamescore / 10);
                    score.append(gamescore % 10);
                    score.append(empty, sizeof(empty));
                }
            }

            // Show score animation
            while (!score.isFinished()) {
                display.show(score.render(false));
                last_action = curr_time;
                wait_ms(100);

                if (ButtonHandler::get_button_state_l() && ButtonHandler::get_button_state_r()) {
                    game.reset();
                    reset_score();
                    last_step = curr_time;
                    break;
                }
            }

            display.show(game.render());
            //if (blink) {
            //    display.show(game.render());
            //} else {
            //    display.show(empty_frame);
            //}

            //if (curr_time > last_step + delay(game.getScore())) {
            //    blink = !blink;
            //    last_step = curr_time;
            //}
        } else {
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
            last_action = curr_time;
        }

    }


    return 0;
}


ISR(PCINT1_vect) {
    // The interrupt is just used for wakeup. No further actions necessary.
}
