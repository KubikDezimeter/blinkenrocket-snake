#include "Snake.h"

const Coordinates* Snake::getBody() const {
    return body;
}

uint8_t Snake::getLength() const {
    return length;
}

uint8_t Snake::getHeadIndex() const {
    return head_index;
}

uint8_t Snake::getTailIndex() const {
    return tail_index;
}

Direction Snake::getBodyDirection() const {
    Direction body_dir {};
    Coordinates head { body[head_index] };
    Coordinates second_segment { body[(head_index + 63) % 64] };

    if (head.x == second_segment.x && head.y == second_segment.y - 1) {
        body_dir = down;
    }
    else if (head.x == second_segment.x && head.y == second_segment.y + 1) {
        body_dir = up;
    }
    else if (head.x == second_segment.x - 1 && head.y == second_segment.y) {
        body_dir = right;
    }
    else if (head.x == second_segment.x + 1 && head.y == second_segment.y) {
        body_dir = left;
    }

    return body_dir;
}

Coordinates Snake::getNextHead() const {
    Coordinates next_head {body[head_index]};
    switch (direction) {
        case up:
            next_head.y -= 1;
            break;
        case left:
            next_head.x -= 1;
            break;
        case down:
            next_head.y += 1;
            break;
        case right:
            next_head.x += 1;
            break;
    }

    return next_head;
}

void Snake::reset() {
    body[0] = {1, 2};
    body[1] = {2, 2};
    body[2] = {3, 2};
    head_index = 2;
    tail_index = 0;
    length = 3;
    direction = right;
}

void Snake::move(bool grow) {
    uint8_t next_head_index = (head_index + 1) % 64;
    Coordinates next_head = getNextHead();

    body[next_head_index] = next_head;
    head_index = next_head_index;

    if (!grow) {
        tail_index = (tail_index + 1) % 64;
    }
}

void Snake::turnLeft() {
    switch (direction) {
        case up:
            if (getBodyDirection() != left) { direction = left; }
            break;
        case left:
            if (getBodyDirection() != down) { direction = down; }
            break;
        case down:
            if (getBodyDirection() != right) { direction = right; }
            break;
        case right:
            if (getBodyDirection() != up) { direction = up; }
            break;
    }
}

void Snake::turnRight() {
    switch (direction) {
        case up:
            if (getBodyDirection() != right) { direction = right; }
            break;
        case right:
            if (getBodyDirection() != down) { direction = down; }
            break;
        case down:
            if (getBodyDirection() != left) { direction = left; }
            break;
        case left:
            if (getBodyDirection() != up) { direction = up; }
            break;
    }
}

bool Snake::checkCollision(Coordinates coordinates) const {
    for (int i = tail_index; i != (head_index + 1) % 64; i = (i + 1) % 64) {
        if (body[i] == coordinates) {
            return true;
        }
    }

    return false;
}
