#include "Paddle.h"
#include <cstdint>

int8_t Paddle::getPosition() const {
    return position;
}

void Paddle::move_left() {
    if (position > 0)
        position -= 1;
}

void Paddle::move_right() {
    if (position < 6)
        position += 1;
}
