#include "ButtonHandler.h"


ButtonHandler::ButtonHandler() {
    // Enable pull-up resistors on button pins
    PORTC |= _BV(PC3) | _BV(PC7);
}

ButtonHandler& ButtonHandler::getButtonHandler() {
    static ButtonHandler instance;
    return instance;
}

bool ButtonHandler::get_button_state_l() {
    return (PINC & _BV(PC7)) == 0;
}

bool ButtonHandler::get_button_state_r() {
    return (PINC & _BV(PC3)) == 0;
}

bool ButtonHandler::update_button_press_l(uint32_t current_time) {
    bool button_pressed = false;

    bool curr_button_state = get_button_state_l();

    if (curr_button_state && !prev_button_l && current_time > button_l_cooldown) {
        button_l_cooldown = current_time + 20;
        button_pressed = true;
    }
    
    // Set cooldown after button release to ignore bounces
    if (!curr_button_state && prev_button_l) {
        button_l_cooldown = current_time + 20;
    }

    prev_button_l = curr_button_state;

    return button_pressed;
}

bool ButtonHandler::update_button_press_r(uint32_t current_time) {
    bool button_pressed = false;

    bool curr_button_state = get_button_state_r();

    if (curr_button_state && !prev_button_r && current_time > button_r_cooldown) {
        button_r_cooldown = current_time + 20;
        button_pressed = true;
    }
    
    // Set cooldown after button release to ignore bounces
    if (!curr_button_state && prev_button_r) {
        button_r_cooldown = current_time + 20;
    }

    prev_button_r = curr_button_state;

    return button_pressed;
}
