#ifndef SIGNAL_RENDERER_H
#define SIGNAL_RENDERER_H

#include <stdint.h>
#include "assert.h"
#include "Frame.h"
class SignalRenderer {
    public:
        SignalRenderer(uint8_t stretch_width);
        void set_signal(uint32_t signal, int8_t index);
        void new_signal();
        void push(bool value);
        Frame render();

    private:
        uint32_t signal {};
        int8_t index { 0 };
        const uint8_t stretch_width {};
        uint8_t stretch_counter {};
};

#endif
