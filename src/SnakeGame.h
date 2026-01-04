#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Snake.h"
#include "Coordinates.h"
#include "Frame.h"
#include "Random.h"

class SnakeGame {
    private:
        bool gameover { false };
        uint8_t score;
        Snake snake;
        Coordinates food {  };

        void generate_food();

    public:
        SnakeGame();
        uint8_t getScore() const;
        void pressLeft();
        void pressRight();
        void step();
        Frame render() const;
};

#endif
