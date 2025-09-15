#include "Game.h"
#include <cstdint>

Frame Game::render() const {
    Frame frame {};

    // Render ball
    frame.setPixel(ball.getPosition());

    // Render paddle
    frame.setPixel(paddle.getPosition(), 7);
    frame.setPixel(paddle.getPosition() + 1, 7);

    // Render wall
    for (uint8_t y {0}; y < 4; ++y) {
        for (uint8_t x {0}; x < 8; ++x) {
            if (wall.is_block(x, y))
                frame.setPixel(x, y);
        }
    }

    return frame;
}
