#ifndef FRAME_H_
#define FRAME_H_

#include "Coordinates.h"
#include <stdint.h>
//#include <ostream>

class Frame {
    private:
        /**
         * Holds the pixel data rowwise. Rows are ordered from top to bottom. The MSB is the leftmost pixel, the LSB is the rightmost pixel.
         */
        uint8_t frame[8] {};

    public:
        Frame() = default;
        Frame(const volatile uint8_t* data);
        void setPixel(Coordinates coordinates);
        void setPixel(uint8_t x, uint8_t y);
        void clearPixel(Coordinates coordinates);
        void clearPixel(uint8_t x, uint8_t y);
        void transpose();
        uint8_t rowByte(uint8_t row) const;
        //bool** begin();
        //bool** end();
        //const bool** begin() const;
        //const bool** end() const;
        //friend std::ostream& operator<<(std::ostream& out, const Frame& frame);
};

#endif
