#ifndef PADDLE_H_
#define PADDLE_H_

#include <cstdint>

class Paddle {
    private:
        /// X coordinate of the left half of the paddle
        uint8_t position {3};

    public:
        uint8_t getPosition() const;
        void move_left();
        void move_right();
};

#endif
