#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Frame.h"

class Display {
    public:
        virtual void show(Frame frame) const = 0;
};

#endif
