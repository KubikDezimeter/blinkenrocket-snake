#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"

class Animation {
    public:
        Animation(const uint8_t* columns, const uint8_t col_count) : columns(columns), col_count(col_count), offset(0) {};
        void setOffset(uint8_t offset);
        bool isFinished() const;
        Frame render(bool loop=false);

    private:
        /*
         * MSB is the top pixel, LSB is the bottom pixel. Columns are ordered from left to right.
         */
        const uint8_t* columns;
        const uint8_t col_count;
        uint8_t offset;
};

#endif
