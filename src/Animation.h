#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>
#include "Font.h"
#include "Frame.h"

class Animation {
    public:
        Animation(uint8_t* const columns, const uint8_t col_count, const uint8_t capacity=0);
        uint8_t getOffset() const;
        void setOffset(uint8_t offset);
        void append(const uint8_t* columns, const uint8_t col_count);
        void appendChar(glyph_t);
        bool isFinished() const;
        Frame render(bool loop=false);

    private:
        /*
         * MSB is the top pixel, LSB is the bottom pixel. Columns are ordered from left to right.
         */
        uint8_t* const columns;
        uint8_t col_count;
        const uint8_t capacity;
        uint8_t offset;
};

#endif
