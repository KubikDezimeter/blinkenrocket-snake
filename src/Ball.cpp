#include "Ball.h"

Coordinates Ball::getPosition() const {
    return position;
}

Vector Ball::getVelocity() const {
    return velocity;
}

void Ball::setPosition(Coordinates position) {
    this->position = position;
}

void Ball::setPosition(int8_t x, int8_t y) {
    this->position = Coordinates {x, y};
}

void Ball::setVelocity(Vector velocity) {
    this->velocity = velocity;
}

void Ball::setVelocity(int8_t dx, int8_t dy) {
    this->velocity = Vector {dx, dy};
}
