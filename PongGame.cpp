#include "PongGame.h"

Frame PongGame::render() const {
    Frame frame {};

    // Render ball
    frame.setPixel(ball.getPosition());

    // Render paddle
    frame.setPixel(paddle.getPosition(), 7);
    frame.setPixel(paddle.getPosition() + 1, 7);

    return frame;
}

bool PongGame::step() {
    const Coordinates paddleLeft {paddle.getPosition(), 7};
    const Coordinates paddleRight{static_cast<int8_t>(paddle.getPosition() + 1), 7};

    const Vector currentBallVelocity = ball.getVelocity();
    const Coordinates nextBallPosition {ball.getPosition() + currentBallVelocity};

    if (nextBallPosition.x < 0 || nextBallPosition.x > 7)
        ball.setVelocity(-currentBallVelocity.dx, currentBallVelocity.dy);
    if (nextBallPosition.y < 0)
        ball.setVelocity(currentBallVelocity.dx, -currentBallVelocity.dy);
    if (nextBallPosition.y > 7)
        return true;

    const Coordinates beforeBall {ball.getPosition() + ball.getVelocity()};
    const Coordinates verticalBeforeBall {ball.getPosition().x, static_cast<int8_t>(ball.getPosition().y + ball.getVelocity().dy)};
    const Coordinates horizontalBehindBall {static_cast<int8_t>(ball.getPosition().x - ball.getVelocity().dx), ball.getPosition().y};

    if (verticalBeforeBall == paddleLeft || verticalBeforeBall == paddleRight)
        ball.setVelocity(ball.getVelocity().dx, -ball.getVelocity().dy);
    else if (beforeBall == paddleLeft || beforeBall == paddleRight) {
        if (horizontalBehindBall.x < 0 || horizontalBehindBall.x > 7)
            ball.setVelocity(ball.getVelocity().dx, -ball.getVelocity().dy);
        else
            ball.setVelocity(-ball.getVelocity().dx, -ball.getVelocity().dy);
    }

    ball.setPosition(ball.getPosition() + ball.getVelocity());

    return false;
}
