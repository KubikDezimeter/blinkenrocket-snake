#ifndef HARDWAREDISPLAY_H_
#define HARDWAREDISPLAY_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Display.h"
#include "Frame.h"

class HardwareDisplay : Display {
    public:
        virtual void enable();
        virtual void show(Frame frame) const;
        void multiplex();

    private:
        Frame frame {};
        uint8_t activeRow {0};
};

extern HardwareDisplay display;

#endif
