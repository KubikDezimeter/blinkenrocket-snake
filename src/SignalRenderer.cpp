#include "SignalRenderer.h"

SignalRenderer::SignalRenderer(uint8_t stretch_width) : stretch_width(stretch_width+1), stretch_counter(stretch_width) {};

void SignalRenderer::set_signal(uint32_t signal, int8_t index) {
    this->signal = signal;
    this->index = index;
}

void SignalRenderer::new_signal() {
    bool value_current { static_cast<bool>(signal & 1) };
    uint8_t n { static_cast<uint8_t>(8 % stretch_width == 0 ? 8 / stretch_width : 8 / stretch_width + 1) };

    for (uint8_t i = 0; i < n; ++i) {
        push(value_current);
    }
}

void SignalRenderer::push(bool value) {
    signal = (signal << 1) + (value ? 1 : 0);
    if (index < 31) {
        ++index;
    }
}

Frame SignalRenderer::render() {
    // frame columns, left-to-right
    uint8_t buf[8] {};
    uint8_t stretch_counter_initial { stretch_counter };
    int8_t index_current { index };
    bool edge {};
    bool value_current {};
    bool value_next {};

    for (uint8_t i = 0; i < 8; ++i) {
        // add signal if none is left to render
        if (index_current <= 0) {
            push(static_cast<bool>(signal & 1));
            if (index_current < 31) {
                ++index_current;
            }
        }

        assert(index_current > 0);
        value_current = static_cast<bool>(signal & (static_cast<uint32_t>(1) << index_current));
        value_next = static_cast<bool>(signal & (static_cast<uint32_t>(1) << (index_current - 1)));

        edge = (stretch_counter == 0) && (value_current != value_next);
        
        if (edge) {
            buf[i] = 0b01111110;
        } else {
            buf[i] = value_current ? 0b01000000 : 0b00000010;
        }

        if (stretch_counter == 0) {
            stretch_counter = stretch_width-1;
            --index_current;
        } else {
            --stretch_counter;
        }
    }

    // Decrease stretch_counter by 1 with wraparound back to stretch_width
    stretch_counter = (stretch_counter_initial + stretch_width-1) % (stretch_width);
    if (stretch_counter == stretch_width-1 && index > 0) {
        --index;
    }

    Frame frame {buf};
    frame.transpose();
    return frame;
}
