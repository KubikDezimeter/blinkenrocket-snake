#include "Ball.h"
#include "Frame.h"
#include "Wall.h"
#include "Paddle.h"
#include <array>

class Game {
    private:
        Ball ball;
        Wall wall;
        Paddle paddle;

    public:
        void step();
        Frame render() const;
};
