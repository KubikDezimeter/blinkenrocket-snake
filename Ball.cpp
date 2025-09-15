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

void Ball::setVelocity(Vector velocity) {
    this->velocity = velocity;
}
