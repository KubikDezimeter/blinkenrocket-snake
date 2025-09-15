#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <cstdint>

struct Coordinates {
    int8_t x;
    int8_t y;

    Coordinates(int8_t x, int8_t y) : x(x), y(y) {};
};

#endif
