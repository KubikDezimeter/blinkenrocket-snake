#ifndef FRAME_H_
#define FRAME_H_

#include "Coordinates.h"
#include <array>
#include <cstdint>
#include <ostream>

class Frame {
    private:
        std::array<std::array<bool, 8>, 8> frame {};

    public:
        void setPixel(Coordinates coordinates);
        void setPixel(uint8_t x, uint8_t y);
        void clearPixel(Coordinates coordinates);
        void clearPixel(uint8_t x, uint8_t y);
        std::array<bool, 8>* begin();
        std::array<bool, 8>* end();
        const std::array<bool, 8>* begin() const;
        const std::array<bool, 8>* end() const;
        friend std::ostream& operator<<(std::ostream& out, const Frame& frame);
};

#endif
