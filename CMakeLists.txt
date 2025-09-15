cmake_minimum_required(VERSION 3.22)

project(
    BlinkenrocketBreakout
    LANGUAGES CXX
)

add_executable(Breakout main.cpp Ball.cpp Frame.cpp Game.cpp Paddle.cpp TerminalDisplay.cpp Wall.cpp)
set_property(TARGET Breakout PROPERTY CXX_STANDARD 17)
