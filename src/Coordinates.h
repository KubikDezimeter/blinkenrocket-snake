#ifndef COORDINATES_H_
#define COORDINATES_H_

#include "Vector.h"
#include <stdint.h>

struct Coordinates {
    int8_t x;
    int8_t y;

    Coordinates(int8_t x, int8_t y) : x(x), y(y) {};

    friend Coordinates operator+(const Coordinates& coords, const Vector& vector);
    friend bool operator==(const Coordinates& left, const Coordinates& right);
    friend bool operator!=(const Coordinates& left, const Coordinates& right);
};

#endif
