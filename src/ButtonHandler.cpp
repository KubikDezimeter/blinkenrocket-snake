#include "ButtonHandler.h"


ButtonHandler::ButtonHandler() {
    // Enable pull-up resistors on button pins
    PORTC |= _BV(PC3) | _BV(PC7);
}

ButtonHandler& ButtonHandler::getButtonHandler() {
    static ButtonHandler instance;
    return instance;
}

bool ButtonHandler::get_button_l() {
    return (PINC & _BV(PC7)) == 0;
}

bool ButtonHandler::get_button_r() {
    return (PINC & _BV(PC3)) == 0;
}
