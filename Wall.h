#ifndef WALL_H_
#define WALL_H_

#include "Coordinates.h"
#include <array>
#include <cstdint>
#include <string_view>

class Wall {
    private:
        std::array<std::array<bool, 8>, 4> wall {true};

    public:
        Wall();
        bool is_block(Coordinates coordinates) const;
        bool is_block(uint8_t x, uint8_t y) const;
        void break_block(uint8_t x, uint8_t y);
        friend std::ostream& operator<<(std::ostream& out, const Wall& wall);
};

#endif
