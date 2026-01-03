#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <stdlib.h>
#include <avr/io.h>

class ButtonHandler {
    public:
        static ButtonHandler& getButtonHandler();

        ButtonHandler(ButtonHandler const&) = delete;
        void operator=(ButtonHandler const&) = delete;

        static bool get_button_l();
        static bool get_button_r();

    private:
        ButtonHandler();
};

#endif
