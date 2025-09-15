#ifndef TERMINALDISPLAY_H_
#define TERMINALDISPLAY_H_

#include "Display.h"
#include "Frame.h"
#include <iostream>

class TerminalDisplay : Display {
    public:
        virtual void show(Frame frame) const;
};

#endif
