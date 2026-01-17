#ifndef SNAKE_H
#define SNAKE_H

#include "Coordinates.h"

enum Direction {
    up,
    down,
    left,
    right,
};

class Snake {
    public:
        const Coordinates* getBody() const;
        uint8_t getLength() const;
        uint8_t getHeadIndex() const;
        uint8_t getTailIndex() const;
        Direction getBodyDirection() const;
        Coordinates getNextHead() const;
        void reset();
        void move(bool grow);
        void turnLeft();
        void turnRight();
        bool checkCollision(Coordinates coordinates) const;

    private:
        // ring buffer, snake grows to the right
        Coordinates body[64] { {1, 2}, {2, 2}, {3, 2} };
        uint8_t head_index { 2 };
        uint8_t tail_index { 0 };
        uint8_t length {3};
        Direction direction { right };
};

#endif
