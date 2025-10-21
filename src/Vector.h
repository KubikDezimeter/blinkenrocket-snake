#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstdint>

struct Vector {
    int8_t dx;
    int8_t dy;

    Vector(int8_t delta_x, int8_t delta_y) : dx(delta_x), dy(delta_y) {};

    static const Vector UP;
    static const Vector DOWN;
    static const Vector LEFT;
    static const Vector RIGHT;
};

#endif
