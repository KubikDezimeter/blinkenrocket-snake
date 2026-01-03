#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <stdlib.h>
#include <avr/io.h>

class ButtonHandler {
    public:
        static ButtonHandler& getButtonHandler();

        ButtonHandler(ButtonHandler const&) = delete;
        void operator=(ButtonHandler const&) = delete;

        static bool get_button_state_l();
        static bool get_button_state_r();

        bool update_button_press_l(uint32_t current_time);
        bool update_button_press_r(uint32_t current_time);

    private:
        ButtonHandler();

        bool prev_button_l {false};
        bool prev_button_r {false};

        uint32_t button_l_cooldown {0};
        uint32_t button_r_cooldown {0};
};

#endif
