#include "Wall.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <ostream>

Wall::Wall() {
    for (auto& row : wall) {
        for (auto& block : row) {
            block = true;
        }
    }
}

bool Wall::is_block(uint8_t x, uint8_t y) const {
    return wall.at(y).at(x);
}

void Wall::break_block(uint8_t x, uint8_t y) {
    bool& block = wall.at(y).at(x);
    assert(block);
    block = false;
}

std::ostream& operator<<(std::ostream& out, const Wall& wall) {
    for (auto& row : wall.wall) {
        for (auto& block : row) {
            out << (block ? 1 : 0);
        }
        out << '\n';
    }

    return out;
}
