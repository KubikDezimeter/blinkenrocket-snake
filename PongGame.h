#include "Ball.h"
#include "Frame.h"
#include "Paddle.h"
#include <array>

class PongGame {
    private:
        Ball ball;
        Paddle paddle;

    public:
        /// Returns if the game is over
        bool step();
        Frame render() const;
};
