#include "SnakeGame.h"

SnakeGame::SnakeGame() {
    generate_food();
}

void SnakeGame::generate_food() {
    Coordinates new_food {};
    new_food.x = xorshift32(r) % 8;
    new_food.y = xorshift32(r) % 8;

    while (snake.checkCollision(new_food)) {
        new_food.x = xorshift32(r) % 8;
        new_food.y = xorshift32(r) % 8;
    }
    food = new_food;
}

uint8_t SnakeGame::getScore() const {
    return score;
}

void SnakeGame::pressLeft() {
    snake.turnLeft();
}

void SnakeGame::pressRight() {
    snake.turnRight();
}

void SnakeGame::step() {
    Coordinates next_head = snake.getNextHead();

    // check for collision with wall
    if (next_head.x < 0 || next_head.x >= 8 || next_head.y < 0 || next_head.y >= 8) {
        gameover = true;
        return;
    }

    // check for collision with body
    if (snake.checkCollision(next_head)) {
        gameover = true;
        return;
    }

    // check for collision with food
    bool grow { false };
    if (next_head == food) {
        ++score;
        grow = true;
        generate_food();
    }

    // move
    snake.move(grow);

}

Frame SnakeGame::render() const {
    Frame frame {};

    if (gameover) {
        uint8_t gameover_screen[8] {
            0b00111100,
            0b01111110,
            0b11011011,
            0b11111111,
            0b11100111,
            0b11011011,
            0b01111110,
            0b00111100,
        };
        return Frame { gameover_screen };
    }

    // draw snake
    for (int i = snake.getTailIndex(); i != (snake.getHeadIndex() + 1) % 64; i = (i + 1) % 64) {
        frame.setPixel(snake.getBody()[i]);
    }

    // draw food
    frame.setPixel(food);

    return frame;
}
