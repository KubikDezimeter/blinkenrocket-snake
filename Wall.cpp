#include "Wall.h"

Wall::Wall() {
    for (auto& row : wall) {
        for (auto& block : row) {
            block = true;
        }
    }
}

bool Wall::is_block(int8_t x, int8_t y) const {
    return wall.at(y).at(x);
}

bool Wall::is_block(Coordinates coordinates) const {
    return is_block(coordinates.x, coordinates.y);
}

bool Wall::is_border(int8_t x, int8_t y) const {
    return (x < 0 || x > 7 || y < 0 || y > 7);
}

bool Wall::is_border(Coordinates coordinates) const {
    return is_border(coordinates.x, coordinates.y);
}

bool Wall::is_free(int8_t x, int8_t y) const {
    return (!is_block(x, y) && !is_border(x, y));
}

bool Wall::is_free(Coordinates coordinates) const {
    return is_free(coordinates.x, coordinates.y);
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
