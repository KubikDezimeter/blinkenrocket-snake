cmake_minimum_required(VERSION 3.22)

project(
    BlinkenrocketBreakout
    LANGUAGES CXX
)

add_executable(Breakout main.cpp Ball.cpp Coordinates.cpp Frame.cpp Game.cpp Paddle.cpp PongGame.cpp TerminalDisplay.cpp Vector.cpp Wall.cpp)
set_property(TARGET Breakout PROPERTY CXX_STANDARD 17)
